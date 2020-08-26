
#include "CrossTieMesh.h"

// Initialise vertex data, buffers and load texture.
CrossTieMesh::CrossTieMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int lresolution)
{
	cross_tie_count_ = 0;

	resolution = lresolution;
	initBuffers(device);

	device_context_ = deviceContext;

	prev_index_count_ = 0;

}


CrossTieMesh::~CrossTieMesh()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}

void CrossTieMesh::AddCrossTie(XMVECTOR left, XMVECTOR right, XMVECTOR up, XMVECTOR forward)
{
	VertexType vertex0, vertex1, vertex2;
	
	//	BACK FACE.
	vertex0.position = XMFLOAT3(XMVectorGetX(left), XMVectorGetY(left), XMVectorGetZ(left));
	vertex1.position = XMFLOAT3(XMVectorGetX(right), XMVectorGetY(right), XMVectorGetZ(right));
	vertex2.position = XMFLOAT3(XMVectorGetX(up), XMVectorGetY(up), XMVectorGetZ(up));

	vertex0.normal = XMFLOAT3(XMVectorGetX(-forward), XMVectorGetY(-forward), XMVectorGetZ(-forward));
	vertex1.normal = XMFLOAT3(XMVectorGetX(-forward), XMVectorGetY(-forward), XMVectorGetZ(-forward));
	vertex2.normal = XMFLOAT3(XMVectorGetX(-forward), XMVectorGetY(-forward), XMVectorGetZ(-forward));

	vertices_.push_back(vertex0);
	vertices_.push_back(vertex1);
	vertices_.push_back(vertex2);

	indices_.push_back(0 + (cross_tie_count_ * 3));
	indices_.push_back(1 + (cross_tie_count_ * 3));
	indices_.push_back(2 + (cross_tie_count_ * 3));
	
	cross_tie_count_++;
	
	//	FRONT FACE.
	vertex0.position = XMFLOAT3(XMVectorGetX(left), XMVectorGetY(left), XMVectorGetZ(left));
	vertex1.position = XMFLOAT3(XMVectorGetX(right), XMVectorGetY(right), XMVectorGetZ(right));
	vertex2.position = XMFLOAT3(XMVectorGetX(up), XMVectorGetY(up), XMVectorGetZ(up));

	vertex0.normal = XMFLOAT3(XMVectorGetX(-forward), XMVectorGetY(-forward), XMVectorGetZ(-forward));
	vertex1.normal = XMFLOAT3(XMVectorGetX(-forward), XMVectorGetY(-forward), XMVectorGetZ(-forward));
	vertex2.normal = XMFLOAT3(XMVectorGetX(-forward), XMVectorGetY(-forward), XMVectorGetZ(-forward));

	vertices_.push_back(vertex0);
	vertices_.push_back(vertex1);
	vertices_.push_back(vertex2);

	indices_.push_back(2 + (cross_tie_count_ * 3));
	indices_.push_back(1 + (cross_tie_count_ * 3));
	indices_.push_back(0 + (cross_tie_count_ * 3));

	cross_tie_count_++;
}

// Initialise geometry buffers (vertex and index).
// Generate and store cube vertices, normals and texture coordinates
void CrossTieMesh::initBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// 6 vertices per quad, res*res is face, times 6 for each face
	vertexCount = 3000;

	indexCount = vertexCount;

	// Create the vertex and index array.
	vertices = new VertexType[vertexCount];
	indices = new unsigned long[indexCount];

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

void CrossTieMesh::Update()
{
	if (vertices_.empty())
	{
		return;
	}

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
	indices = (unsigned long*)index_mapped_resource.pData;

	//	If the number of vertices has been reduced then make sure the old indices are overwritten.
	if (indices_.size() < prev_index_count_)
	{
		for (int k = indices_.size(); k < prev_index_count_; k++)
		{
			indices_.push_back(-1);
		}
	}

	for (int i = 0; i < indices_.size(); i++)
	{
		indices[i] = indices_[i];
	}


	device_context_->Unmap(indexBuffer, 0);

	prev_index_count_ = indices_.size();

	vertices_.clear();
	indices_.clear();
	cross_tie_count_ = 0;

}

