#include "MeshInstance.h"

MeshInstance::MeshInstance(ID3D11ShaderResourceView* texture, BaseShader* shader, BaseMesh* mesh) : 
	world_matrix_(DirectX::XMMatrixIdentity()), texture_(texture), shader_(shader), mesh_(mesh)
{
	shader_->SetTexture(texture_);
}
MeshInstance::MeshInstance(BaseShader* shader, BaseMesh* mesh) :
	world_matrix_(DirectX::XMMatrixIdentity()), texture_(nullptr), shader_(shader), mesh_(mesh)
{
	shader_->SetTexture(texture_);
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
	if (shader_->GetShaderType() == SHADERTYPE::DEFAULT)
	{
		DefaultShader* shader = (DefaultShader*)shader_;
		shader->setShaderParameters(device_context, world_matrix_, view, projection);
		mesh_->sendData(device_context);
		shader->render(device_context, mesh_->getIndexCount());
	}

	if (shader_->GetShaderType() == SHADERTYPE::COLOUR)
	{
		ColourShader* shader = (ColourShader*)shader_;
		shader->setShaderParameters(device_context, world_matrix_, view, projection);
		mesh_->sendData(device_context);
		shader->render(device_context, mesh_->getIndexCount());
	}

	
	return true;
}

void MeshInstance::SetWorldMatrix(XMMATRIX wm)
{
	world_matrix_ = wm;
}
