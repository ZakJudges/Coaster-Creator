#include "MeshInstance.h"

MeshInstance::MeshInstance(ID3D11ShaderResourceView* texture, BaseShader* shader, BaseMesh* mesh) : 
	transform_(DirectX::XMMatrixIdentity()), texture_(texture), shader_(shader), mesh_(mesh)
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

bool MeshInstance::Render(ID3D11DeviceContext* device_context)
{
	

	return false;

}
