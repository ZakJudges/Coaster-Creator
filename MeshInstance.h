#pragma once

#include "../DXFramework/Geometry.h"
#include <DirectXMath.h>
#include "ColourShader.h"
#include "DefaultShader.h"

class MeshInstance
{
public:
	MeshInstance(ID3D11ShaderResourceView* texture, BaseShader* shader, BaseMesh* mesh);
	~MeshInstance();
	bool Render(ID3D11DeviceContext*);
protected:
	XMMATRIX transform_;
	BaseShader* shader_;
	ID3D11ShaderResourceView* texture_;
	BaseMesh* mesh_;
};