#include "TrackMesh.h"

TrackMesh::TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader)
{
	PipeMesh* rail_mesh = new PipeMesh(device, deviceContext, 0.1f);
	rail_meshes_.push_back(rail_mesh);
	rail_mesh = new PipeMesh(device, deviceContext, 0.1f);
	rail_meshes_.push_back(rail_mesh);

	MeshInstance* rail = new MeshInstance(nullptr, shader, rail_meshes_[0]);
	rails_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[1]);
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

	rail_meshes_[0]->AddCircleOrigin(centre - (x_axis * 0.5f), x_axis, y_axis);
	rail_meshes_[1]->AddCircleOrigin(centre + (x_axis * 0.5f), x_axis, y_axis);

}

void TrackMesh::Update()
{
	rail_meshes_[0]->Update();
	rail_meshes_[1]->Update();
}

TrackMesh::~TrackMesh()
{

}