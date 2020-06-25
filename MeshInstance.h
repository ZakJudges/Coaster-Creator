#pragma once

#include "../DXFramework/Geometry.h"
#include <DirectXMath.h>
#include "ColourShader.h"
#include "DefaultShader.h"

class MeshInstance
{
public:
	MeshInstance(ID3D11ShaderResourceView* texture, BaseShader* shader, BaseMesh* mesh);
	MeshInstance(BaseShader* shader, BaseMesh* mesh);
	~MeshInstance();
	bool Render(ID3D11DeviceContext* context, XMMATRIX& view, XMMATRIX& projection);
	void SetScaleMatrix(XMFLOAT3 scale);
	void SetWorldMatrix(XMMATRIX wm);
	XMMATRIX GetWorldMatrix();
private:
protected:
	XMMATRIX world_matrix_;
	XMMATRIX scale_matrix_;
	BaseShader* shader_;
	ID3D11ShaderResourceView* texture_;
	BaseMesh* mesh_;
	XMFLOAT4 colour_;	//to remove.
};