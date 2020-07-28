#include "MeshInstance.h"

MeshInstance::MeshInstance(ID3D11ShaderResourceView* texture, BaseShader* shader, BaseMesh* mesh) : 
	world_matrix_(DirectX::XMMatrixIdentity()), texture_(texture), shader_(shader), mesh_(mesh)
{
	shader_->SetTexture(texture_);

	SetScaleMatrix(XMFLOAT3(1.0f, 1.0f, 1.0f));
}

MeshInstance::MeshInstance(BaseShader* shader, BaseMesh* mesh) :
	world_matrix_(DirectX::XMMatrixIdentity()), texture_(nullptr), shader_(shader), mesh_(mesh)
{
	shader_->SetTexture(texture_);

	SetScaleMatrix(XMFLOAT3(1.0f, 1.0f, 1.0f));

}

MeshInstance::~MeshInstance()
{
	if (shader_)
	{
		delete shader_;
		shader_ = 0;
	}

	if (texture_)
	{
		delete texture_;
		texture_ = 0;
	}

	if (mesh_)
	{
		delete mesh_;
		mesh_ = 0;
	}
}

bool MeshInstance::Render(ID3D11DeviceContext* device_context, XMMATRIX& view, XMMATRIX& projection)
{
	shader_->SetTexture(texture_);
	shader_->SetColour(colour_.x, colour_.y, colour_.z);

	shader_->SetShaderParameters(device_context, world_matrix_, view, projection);
	mesh_->sendData(device_context);
	shader_->render(device_context, mesh_->getIndexCount());

	return true;
}

void MeshInstance::SetScaleMatrix(XMFLOAT3 scale)
{
	scale_matrix_ = XMMatrixScaling(scale.x, scale.y, scale.z);
	SetWorldMatrix(world_matrix_);
}

void MeshInstance::SetWorldMatrix(XMMATRIX wm)
{
	world_matrix_ = scale_matrix_ * wm;
}

XMMATRIX MeshInstance::GetWorldMatrix()
{/*
	XMMATRIX world = world_matrix_;
	XMMATRIX scale_matrix = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	world *= XMMatrixInverse(nullptr, scale_matrix);

	return world;*/

	return world_matrix_;
	
}
