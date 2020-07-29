#pragma once

#include "../DXFramework/BaseMesh.h"

using namespace DirectX;

class CrossTieMesh : public BaseMesh
{

public:
	CrossTieMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 20);
	void Update();
	~CrossTieMesh();

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;
};
