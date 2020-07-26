
#pragma once

#include "../DXFramework/BaseMesh.h"
#include <vector>

using namespace DirectX;

class PipeMesh : public BaseMesh
{

public:
	PipeMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 20);
	void Update();
	void GenerateCirclePoints(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis);
	void sendData(ID3D11DeviceContext* deviceContext);
	~PipeMesh();

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;

private:
	ID3D11DeviceContext* device_context_;
	std::vector<VertexType> vertices_;
	std::vector<unsigned long int> indices_;

	unsigned int circle_count_;
	unsigned int slice_count_;
	float radius_;
};

