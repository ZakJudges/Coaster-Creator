// Cube Mesh
// Generates cube mesh at set resolution. Default res is 20.
// Mesh has texture coordinates and normals.
#include "PipeMesh.h"
#include <math.h>

// Initialise vertex data, buffers and load texture.
PipeMesh::PipeMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int lresolution)
{
	device_context_ = deviceContext;
	resolution = lresolution;

	circle_count_ = 1;
	radius_ = 3.0f;
	slice_count_ = 20;

	initBuffers(device);

}

PipeMesh::~PipeMesh()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}

// Initialise geometry buffers (vertex and index).
// Generate and store cube vertices, normals and texture coordinates
void PipeMesh::initBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexCount = 1000;
	indexCount = 2 * vertexCount;
	
	vertices = new VertexType[vertexCount];
	indices = new unsigned long[indexCount];
	
	XMVECTOR centre = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR x_axis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	x_axis = XMVector3Normalize(x_axis);
	XMVECTOR y_axis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	y_axis = XMVector3Normalize(y_axis);

	GenerateCirclePoints(centre, x_axis, y_axis);

	centre = XMVectorSet(10.0f, 0.0f, 0.0f, 0.0f);
	GenerateCirclePoints(centre, x_axis, y_axis);


	for (int i = 0; i < indices_.size(); i++)
	{
		indices[i] = indices_[i];
	}
	for (int i = 0; i < vertices_.size(); i++)
	{
		vertices[i] = vertices_[i];
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;
}

void PipeMesh::Update()
{
	//	Update the vertex buffer.
	D3D11_MAPPED_SUBRESOURCE vertex_mapped_resource;

	VertexType* vertices;// = new VertexType[resolution_];

	device_context_->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vertex_mapped_resource);

	//	Update vertex and index data here.
	vertices = (VertexType*)vertex_mapped_resource.pData;

	for (int i = 0; i < vertices_.size(); i++)
	{
		vertices[i] = vertices_[i];
	}

	device_context_->Unmap(vertexBuffer, 0);


	//	Update the index buffer.
	D3D11_MAPPED_SUBRESOURCE index_mapped_resource;

	unsigned long* indices;

	device_context_->Map(indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &index_mapped_resource);

	//	Update vertex and index data here.
	indices = (unsigned long*)vertex_mapped_resource.pData;

	for (int i = 0; i < indices_.size(); i++)
	{
		indices[i] = indices_[i];
	}

	device_context_->Unmap(indexBuffer, 0);
}

void PipeMesh::GenerateCirclePoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis)
{

	float slice_angle = 2.0f * 3.14159265359f / slice_count_;

	int first_index = (circle_count_ - 1) * 20;

	for (int i = 0; i < slice_count_; i++)
	{
		VertexType vertex;
		XMVECTOR pos = centre + (radius_ * cosf(slice_angle * i) * x_axis) + (radius_ * sinf(slice_angle * i) * y_axis);
		vertex.position = XMFLOAT3(XMVectorGetX(pos), XMVectorGetY(pos), XMVectorGetZ(pos));

		XMVECTOR normal = XMVector3Normalize(pos - centre);
		vertex.normal = XMFLOAT3(XMVectorGetX(normal), XMVectorGetY(normal), XMVectorGetZ(normal));

		vertices_.push_back(vertex);

		if ((first_index + i) != first_index)
		{
			indices_.push_back(first_index + i);
			indices_.push_back(first_index + i);
		}
		else
		{
			indices_.push_back(first_index);
		}
	}
	indices_.push_back(first_index);

	circle_count_ += 1;
}

void PipeMesh::sendData(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
}


