#pragma once

#include "../DXFramework/BaseMesh.h"
#include "../Splines/CRSplineController.h"

class SplineMesh : public BaseMesh
{
public:
	SplineMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* file_name, int resolution = 1000);
	void sendData(ID3D11DeviceContext* deviceContext);
	~SplineMesh();

protected:
	void initBuffers(ID3D11Device* device);

private:
	SL::CRSplineController* spline_controller_;
	int resolution_;
};