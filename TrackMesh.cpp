#include "TrackMesh.h"

TrackMesh::TrackMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BaseShader* shader) : device_(device), device_context_(deviceContext), shader_(shader)
{
	update_instances_ = false;


	//	Simulating Mesh:----------------------------------------------------------------------------
	PipeMesh* rail_mesh = new PipeMesh(device, deviceContext, 0.06f);
	rail_meshes_.push_back(rail_mesh);
	rail_mesh = new PipeMesh(device, deviceContext, 0.06f);
	rail_meshes_.push_back(rail_mesh);
	rail_mesh = new PipeMesh(device, deviceContext, 0.26f);
	rail_mesh->SetSliceCount(6);
	rail_meshes_.push_back(rail_mesh);

	MeshInstance* rail = new MeshInstance(nullptr, shader, rail_meshes_[0]);
	rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	simulating_instances_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[1]);
	rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	simulating_instances_.push_back(rail);
	rail = new MeshInstance(nullptr, shader, rail_meshes_[2]);	//Large
	rail->SetColour(XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f));
	simulating_instances_.push_back(rail);

	CrossTieMesh* cross_ties_mesh = new CrossTieMesh(device, deviceContext);
	cross_ties_meshes_.push_back(cross_ties_mesh);
	MeshInstance* cross_ties = new MeshInstance(nullptr, shader, cross_ties_meshes_[0]);
	cross_ties->SetColour(XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f));
	simulating_instances_.push_back(cross_ties);


	//	Preview mesh:-------------------------------------------------------------------------------
	PipeMesh* preview_rail_mesh = new PipeMesh(device, deviceContext, 0.06f);
	rail_meshes_.push_back(preview_rail_mesh);
	preview_rail_mesh = new PipeMesh(device, deviceContext, 0.06f);
	rail_meshes_.push_back(preview_rail_mesh);
	preview_rail_mesh = new PipeMesh(device, deviceContext, 0.26f);
	rail_meshes_.push_back(preview_rail_mesh);

	CrossTieMesh* preview_cross_tie_mesh = new CrossTieMesh(device, deviceContext);
	cross_ties_meshes_.push_back(preview_cross_tie_mesh);
	


	MeshInstance* preview_rail = new MeshInstance(nullptr, shader, rail_meshes_[3]);
	preview_rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	preview_instances_.push_back(preview_rail);
	preview_rail = new MeshInstance(nullptr, shader, rail_meshes_[4]);
	preview_rail->SetColour(XMFLOAT4(0.46f, 0.62f, 0.8f, 0.0f));
	preview_instances_.push_back(preview_rail);
	preview_rail = new MeshInstance(nullptr, shader, rail_meshes_[5]);
	preview_rail->SetColour(XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f));
	preview_instances_.push_back(preview_rail);

	MeshInstance* preview_cross_ties = new MeshInstance(nullptr, shader, cross_ties_meshes_[1]);
	preview_cross_ties->SetColour(XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f));
	preview_instances_.push_back(preview_cross_ties);


	//SUPPORT STRUCTURE MESHES------------------------------------------------------------------

	sphere_mesh_ = new SphereMesh(device, deviceContext);
	/*support_mesh_ = new PipeMesh(device, deviceContext, 0.2f);
	support_mesh_->SetContinuous(false);
	support_mesh_->SetCirclesPerPipe(2);
	support_mesh_->SetSliceCount(8);
	MeshInstance* support = new MeshInstance(nullptr, shader, support_mesh_);
	simulating_instances_.push_back(support);*/
}

void TrackMesh::StorePoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis)
{
	rail_meshes_[0]->AddCircleOrigin(centre - (x_axis * 0.35f), x_axis, y_axis);
	rail_meshes_[1]->AddCircleOrigin(centre + (x_axis * 0.35f), x_axis, y_axis);
	rail_meshes_[2]->AddCircleOrigin(centre - (y_axis * 0.30f), x_axis, y_axis);
}

void TrackMesh::AddCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis)
{
	cross_ties_meshes_[0]->AddCrossTie(centre, x_axis * -0.35f, x_axis * 0.35f, y_axis * 0.25f, z_axis * 0.05f);

	//cross_ties_meshes_[0]->AddCrossTie(centre, centre - (x_axis * 0.35f), centre + (x_axis * 0.35f), centre - (y_axis * 0.25f), z_axis);
}

void TrackMesh::AddPreviewCrossTie(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis)
{
	//cross_ties_meshes_[1]->AddCrossTie(centre, centre - (x_axis * 0.35f), centre + (x_axis * 0.35f), centre - (y_axis * 0.25f), z_axis);

	cross_ties_meshes_[1]->AddCrossTie(centre, x_axis * -0.35f, x_axis * 0.35f, y_axis * 0.25f, z_axis * 0.05f);
}

void TrackMesh::AddSupportVertical(XMVECTOR from, XMVECTOR to)
{
	/*XMVECTOR world_right, world_forward;
	world_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	world_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	
	XMVECTOR mid = (from + to) / 2;
	
	
	support_mesh_->AddCircleOrigin(to, world_forward, world_right);
	support_mesh_->AddCircleOrigin(mid, world_forward, world_right);
	support_mesh_->AddCircleOrigin(mid , world_forward, world_right);
	support_mesh_->AddCircleOrigin((mid + from) / 2, world_forward, world_right);
	support_mesh_->AddCircleOrigin((mid + from) / 2, world_forward, world_right);
	support_mesh_->AddCircleOrigin(from, world_forward, world_right);*/

	SupportMesh* vertical_support_mesh = new SupportMesh(device_, device_context_, from, to);
	//active_supports_.push_back(vertical_support);

	MeshInstance* vertical_support = new MeshInstance(nullptr, shader_, vertical_support_mesh);
	support_instances_.push_back(vertical_support);

	update_instances_ = true;
}

void TrackMesh::AddSupportSegmented(XMVECTOR vertical_from, XMVECTOR vertical_to, 
	XMVECTOR angled_from, XMVECTOR angled_to, XMVECTOR angled_x, XMVECTOR angled_z)
{
	SupportMesh* segmented_support_mesh = new SupportMesh(device_, device_context_, vertical_from, vertical_to, 
		angled_from, angled_to, angled_x, angled_z);
	//active_supports_.push_back(segmented_support);

	MeshInstance* segmented_support = new MeshInstance(nullptr, shader_, segmented_support_mesh);
	support_instances_.push_back(segmented_support);

	//	Create a new mesh instance of a sphere (reusing the sphere mesh object)
	//		Place the mesh instance at the point where the support pillar is segmented
	//			Should cover where the 'twist' of vertices is seen.

	MeshInstance* sphere_joint = new MeshInstance(nullptr, shader_, sphere_mesh_);
	XMMATRIX sphere_matrix = XMMatrixTranslation(XMVectorGetX(vertical_from), XMVectorGetY(vertical_from), XMVectorGetZ(vertical_from));
	XMMATRIX scale_matrix = XMMatrixScaling(0.19f, 0.19f, 0.19f);
	sphere_joint->SetWorldMatrix(scale_matrix * sphere_matrix);
	support_instances_.push_back(sphere_joint);

	update_instances_ = true;

}

//void TrackMesh::AddSupportElbow(XMVECTOR location, XMVECTOR forward, XMVECTOR right)
//{
//	XMVECTOR world_right, world_forward;
//	world_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//	world_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//
//	support_mesh_->AddCircleOrigin(location, forward, right);
//	support_mesh_->AddCircleOrigin(location, world_forward, world_right);
//}



//void TrackMesh::AddSupport(XMVECTOR from, XMVECTOR to, XMVECTOR forward, XMVECTOR up)
//{
//
//
//	//XMVECTOR mid = (from + to) / 2;
//
//
//	support_mesh_->AddCircleOrigin(from, forward, up);
//	support_mesh_->AddCircleOrigin(to, forward, up);
//	//support_mesh_->AddCircleOrigin(mid, world_forward, world_right);
//	//support_mesh_->AddCircleOrigin((mid + from) / 2, world_forward, world_right);
//	//support_mesh_->AddCircleOrigin((mid + from) / 2, world_forward, world_right);
//	//support_mesh_->AddCircleOrigin(from, world_forward, world_right);
//
//}



void TrackMesh::StorePreviewPoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis, XMVECTOR z_axis)
{
	rail_meshes_[3]->AddCircleOrigin(centre - (x_axis * 0.35f), x_axis, y_axis);
	rail_meshes_[4]->AddCircleOrigin(centre + (x_axis * 0.35f), x_axis, y_axis);
	rail_meshes_[5]->AddCircleOrigin(centre - (y_axis * 0.3f), x_axis, y_axis);
}

void TrackMesh::UpdateSimulatingMesh()
{
	for (int i = 0; i < rail_meshes_.size(); i++)
	{
		rail_meshes_[i]->Update();
	}

	///rail_meshes_[0]->Update();
	///rail_meshes_[1]->Update();
	//rail_meshes_[2]->Update();

	cross_ties_meshes_[0]->Update();
	cross_ties_meshes_[1]->Update();
}

//void TrackMesh::UpdateSupportMesh()
//{
//	support_mesh_->Update();
//}

void TrackMesh::SetPreviewActive(bool preview)
{
	for (int i = 0; i < preview_instances_.size(); i++)
	{
		preview_instances_[i]->SetRender(preview);
	}
}

//void TrackMesh::UpdateBuildingMesh(SL::CRSplineController* spline_controller)
//{
//	if (spline_mesh_)
//	{
//		spline_mesh_->Update(spline_controller);
//	}
//}

void TrackMesh::UpdatePreviewMesh()
{
	rail_meshes_[3]->Update();
	rail_meshes_[4]->Update();
	rail_meshes_[5]->Update();

	cross_ties_meshes_[1]->Update();
}

//void TrackMesh::SetBuildingState()
//{
//	//	Do not render simulating state instances.
//	//for (int i = 0; i < simulating_instances_.size(); i++)
//	//{
//		//simulating_instances_[i]->SetRender(false);
//	//}
//
//	//	Render the building state instances.
//	for (int i = 0; i < building_instances_.size(); i++)
//	{
//		building_instances_[i]->SetRender(true);
//	}
//}
//
//void TrackMesh::SetSimulatingState()
//{
//	//	Render simulating state instances.
//	//for (int i = 0; i < simulating_instances_.size(); i++)
//	//{
//	//	simulating_instances_[i]->SetRender(true);
//	//}
//
//	//	Do not render the building state instances.
//	for (int i = 0; i < building_instances_.size(); i++)
//	{
//		building_instances_[i]->SetRender(false);
//	}
//}

void TrackMesh::SetTranslation(float x, float y, float z)
{
	XMMATRIX world_matrix;
	world_matrix = DirectX::XMMatrixTranslation(x, y, z);

	for (int i = 0; i < simulating_instances_.size(); i++)
	{
		simulating_instances_[i]->SetWorldMatrix(world_matrix);
	}

	for (int i = 0; i < preview_instances_.size(); i++)
	{
		preview_instances_[i]->SetWorldMatrix(world_matrix);
	}

}

XMMATRIX TrackMesh::GetWorldMatrix()
{
	return simulating_instances_[0]->GetWorldMatrix();
}

//SL::Vector TrackMesh::GetTranslation()
//{
//	return translation_;
//}

void TrackMesh::Clear()
{
	//	Clear all of the components making up the track mesh.
	for (int i = 0; i < rail_meshes_.size(); i++)
	{
		rail_meshes_[i]->Clear();
	}

	cross_ties_meshes_[0]->Clear();
	cross_ties_meshes_[1]->Clear();
}

void TrackMesh::ClearPreview()
{
	rail_meshes_[3]->Clear();
	rail_meshes_[4]->Clear();
	rail_meshes_[5]->Clear();

	cross_ties_meshes_[1]->Clear();
}

//void TrackMesh::ClearSupport()
//{
//	support_mesh_->Clear();
//}

unsigned int TrackMesh::GetCrossTieFrequency()
{
	return 2;
}

void TrackMesh::SetSmallRailTexture(ID3D11ShaderResourceView* texture)
{
	if (texture)
	{
		small_rail_texture_ = texture;
	}

	simulating_instances_[0]->SetTexture(small_rail_texture_);
	simulating_instances_[1]->SetTexture(small_rail_texture_);

	preview_instances_[0]->SetTexture(small_rail_texture_);
	preview_instances_[1]->SetTexture(small_rail_texture_);
}

void TrackMesh::SetLargeRailTexture(ID3D11ShaderResourceView* texture)
{
	if (texture)
	{
		large_rail_texture_ = texture;
	}

	simulating_instances_[2]->SetTexture(large_rail_texture_);

	preview_instances_[2]->SetTexture(large_rail_texture_);
	
}

void TrackMesh::SetCrossTieTexture(ID3D11ShaderResourceView* texture)
{
	if (texture)
	{
		cross_tie_texture_ = texture;
	}

	simulating_instances_[3]->SetTexture(cross_tie_texture_);

	preview_instances_[3]->SetTexture(cross_tie_texture_);
}

TrackMesh::~TrackMesh()
{
	for (int i = 0; i < rail_meshes_.size(); i++)
	{
		if (rail_meshes_.at(i));
		{
			delete rail_meshes_[i];
			rail_meshes_[i] = 0;
		}
	}

	for (int i = 0; i < simulating_instances_.size(); i++)
	{
		if (simulating_instances_.at(i));
		{
			delete simulating_instances_[i];
			simulating_instances_[i] = 0;
		}
	}

	for (int i = 0; i < cross_ties_meshes_.size(); i++)
	{
		if (cross_ties_meshes_[i])
		{
			delete cross_ties_meshes_[i];
			cross_ties_meshes_[i] = 0;
		}
	}

	if (sphere_mesh_)
	{
		delete sphere_mesh_;
		sphere_mesh_ = 0;
	}
	//	To Do: delete preview instances and support structure instances.

}

std::vector<MeshInstance*> TrackMesh::GetTrackMeshInstances()
{
	std::vector<MeshInstance*> instances;

	for (int i = 0; i < simulating_instances_.size(); i++)
	{
		instances.push_back(simulating_instances_[i]);
		simulating_instances_[i]->SetRender(true);
	}

	/*for (int i = 0; i < building_instances_.size(); i++)
	{
		instances.push_back(building_instances_[i]);
	}*/

	for (int i = 0; i < preview_instances_.size(); i++)
	{
		instances.push_back(preview_instances_[i]);
		preview_instances_[i]->SetRender(true);
	}

	return instances;
}

//	Any instances that haven't been sent to the application renderer yet.
//		TODO: Extend to allow the addition of all new instances - not just the support instances.
std::vector<MeshInstance*> TrackMesh::GetNewInstances()
{
	update_instances_ = false;
	return support_instances_;
}