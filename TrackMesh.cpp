#include "TrackMesh.h"

TrackMesh::TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader)
{
	PipeMesh* rail_mesh = new PipeMesh(device, deviceContext, 0.05f);
	rail_meshes_.push_back(rail_mesh);
	rail_mesh = new PipeMesh(device, deviceContext, 0.05f);
	rail_meshes_.push_back(rail_mesh);
	rail_mesh = new PipeMesh(device, deviceContext, 0.15f);
	rail_meshes_.push_back(rail_mesh);


	MeshInstance* rail = new MeshInstance(nullptr, shader, rail_meshes_[0]);
	rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	rails_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[1]);
	rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	rails_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[2]);
	rail->SetColour(XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f));
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

	rail_meshes_[0]->AddCircleOrigin(centre - (x_axis * 0.3f), x_axis, y_axis);
	rail_meshes_[1]->AddCircleOrigin(centre + (x_axis * 0.3f), x_axis, y_axis);
	rail_meshes_[2]->AddCircleOrigin(centre - (y_axis * 0.15f), x_axis, y_axis);

}

void TrackMesh::Update()
{
	for (int i = 0; i < rail_meshes_.size(); i++)
	{
		rail_meshes_[i]->Update();
	}
}

TrackMesh::~TrackMesh()
{

}