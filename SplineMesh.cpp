#include "SplineMesh.h"

SplineMesh::SplineMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* file_name, int resolution) : spline_controller_(nullptr)
{
	//	Create the spline using points in the file.
	spline_controller_ = new SL::CRSplineController("points.txt");
	spline_controller_->CreateSegments();
	//spline_controller_->JoinSelf();

	//	As a minimum, there needs to be at lease the same number of points as control points on the spline.
	if (resolution >= spline_controller_->GetNumPoints())
	{
		resolution_ = resolution;
	}
	else
	{
		resolution_ = spline_controller_->GetNumPoints();
	}

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
		indices[i] = i; //	Maybe unneccessary - to be researched.
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

XMVECTOR SplineMesh::GetPointDX(const float t)
{
	SL::Vector point = spline_controller_->GetPoint(t);
	
	XMVECTOR vector = DirectX::XMVectorSet(point.X(), point.Y(), point.Z(), 0.0f);

	return vector;
}

SL::Vector SplineMesh::GetPoint(const float t)
{
	SL::Vector point = spline_controller_->GetPoint(t);
	return point;
}