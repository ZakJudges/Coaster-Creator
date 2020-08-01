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
	simulating_instances_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[1]);
	rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	simulating_instances_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[2]);
	rail->SetColour(XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f));
	simulating_instances_.push_back(rail);

	spline_mesh_ = new SplineMesh(device, deviceContext, 1000);
	MeshInstance* spline = new MeshInstance(nullptr, shader, spline_mesh_);
	spline->SetColour(XMFLOAT4(1.0f, 1.0f, 0.2f, 0.0f));
	building_instances_.push_back(spline);
}

int TrackMesh::GetInstanceCount()
{
	return simulating_instances_.size() + building_instances_.size();
}

MeshInstance* TrackMesh::GetMeshInstance(int element)
{
	if (element < simulating_instances_.size())
	{
		return simulating_instances_[element];
	}
	else
	{
		return building_instances_[element - simulating_instances_.size()];
	}
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

void TrackMesh::SetBuildingState()
{
	//	Do not render simulating state instances.
	for (int i = 0; i < simulating_instances_.size(); i++)
	{
		simulating_instances_[i]->SetRender(false);
	}

	//	Render the building state instances.
	for (int i = 0; i < building_instances_.size(); i++)
	{
		building_instances_[i]->SetRender(true);
	}
}

void TrackMesh::SetSimulatingState()
{
	//	Render simulating state instances.
	for (int i = 0; i < simulating_instances_.size(); i++)
	{
		simulating_instances_[i]->SetRender(true);
	}

	//	Do not render the building state instances.
	for (int i = 0; i < building_instances_.size(); i++)
	{
		building_instances_[i]->SetRender(false);
	}
}

TrackMesh::~TrackMesh()
{

}