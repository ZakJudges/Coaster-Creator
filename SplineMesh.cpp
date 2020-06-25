#include "SplineMesh.h"

SplineMesh::SplineMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution) : spline_controller_(nullptr), resolution_(resolution)
{
	//	Create the spline controller.
	//		Handles all spline logic.
	spline_controller_ = new SL::CRSplineController(resolution);

	SL::Vector p0, p1, p2, p3;

	SL::CRSpline* first = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, -1.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 1.0f);
	p3.Set(0.0f, 0.0f, 2.0f);
	first->SetControlPoints(p0, p1, p2, p3);
	spline_controller_->AddSegment(first, 1.0f);

	SL::CRSpline* second = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, -1.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 1.0f, 1.0f);
	p3.Set(0.0f, 1.0f, 2.0f);
	second->SetControlPoints(p0, p1, p2, p3);
	spline_controller_->AddSegment(second, 1.0f, true);

	SL::CRSpline* third = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, 0.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(1.0f, 0.0f, 1.0f);
	p3.Set(1.0f, 0.0f,0.0f);
	third->SetControlPoints(p0, p1, p2, p3);
	spline_controller_->AddSegment(third, 1.0f, true);

	SL::CRSpline* fourth = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, 1.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 1.0f);
	p3.Set(0.0f, 0.0f, 0.0f);
	fourth->SetControlPoints(p0, p1, p2, p3);
	spline_controller_->AddSegment(fourth, 1.0f, true);


	//spline_controller_->JoinSelf();

	initBuffers(device);
}

SplineMesh::~SplineMesh()
{
	BaseMesh::~BaseMesh();
}

void SplineMesh::initBuffers(ID3D11Device* device)
{
	//	Create vertices for mesh here. TEMP: Triangle mesh.
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	vertexCount = resolution_;
	indexCount = vertexCount;

	vertices = new VertexType[vertexCount];
	indices = new unsigned long[indexCount];

	float t = 0.0f;
	for (int i = 0; i < resolution_; i++)
	{
		SL::Vector point;
		if (i == resolution_ - 1)
		{
			point = spline_controller_->GetPoint(1.0f);
		}
		else
		{
			point = spline_controller_->GetPoint(t);
		}

		vertices[i].position = XMFLOAT3(point.X(), point.Y(), point.Z());
		vertices[i].normal = XMFLOAT3(1.0f, 1.0f, 0.0f);
		indices[i] = i; 
		t += (1.0f / resolution_);
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
}

void SplineMesh::sendData(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

//	Get the point at distance d [0,1] along the spline.
XMFLOAT3 SplineMesh::GetPointAtDistance(const float d)
{
	float t = spline_controller_->GetTimeAtDistance(d);

	SL::Vector point = spline_controller_->GetPoint(t);
	XMFLOAT3 DXpoint = XMFLOAT3(point.X(), point.Y(), point.Z());

	SL::Vector forward = spline_controller_->GetTangent(t);
	forward_ = XMFLOAT3(forward.X(), forward.Y(), forward.Z());

	SL::Vector right = spline_controller_->GetBiTangent(t);
	right_ = XMFLOAT3(right.X(), right.Y(), right.Z());

	SL::Vector up = spline_controller_->GetNormal(t);
	up_ = XMFLOAT3(up.X(), up.Y(), up.Z());

	return DXpoint;
}

XMFLOAT3 SplineMesh::GetForward()
{
	return forward_;
}

XMFLOAT3 SplineMesh::GetRight()
{
	return right_;
}

XMFLOAT3 SplineMesh::GetUp()
{
	return up_;
}
