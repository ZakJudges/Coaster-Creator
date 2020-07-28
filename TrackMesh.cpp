#include "TrackMesh.h"

TrackMesh::TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader)
{
	rail_mesh_ = new PipeMesh(device, deviceContext, 0.1f);

	MeshInstance* rail = new MeshInstance(nullptr, shader, rail_mesh_);
	XMMATRIX m = XMMatrixTranslation(1.0f, 0.0f, 0.0f);
	rail->SetWorldMatrix(m);
	rails_.push_back(rail);

	rail = new MeshInstance(nullptr, shader, rail_mesh_);
	rails_.push_back(rail);
}

int TrackMesh::GetInstanceCount()
{
	return rails_.size();
}

MeshInstance* TrackMesh::GetMeshInstance(int element)
{
	return rails_[element];
}

void TrackMesh::AddPipeMeshCircle(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis)
{
	rail_mesh_->AddCircleOrigin(centre, x_axis, y_axis);
}

void TrackMesh::Update()
{
	rail_mesh_->Update();
}

TrackMesh::~TrackMesh()
{

}