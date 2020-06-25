#pragma once

#include "../DXFramework/BaseMesh.h"
#include "../Splines/CRSplineController.h"

class SplineMesh : public BaseMesh
{
public:
	SplineMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution);
	void sendData(ID3D11DeviceContext* deviceContext);

	XMFLOAT3 GetPointAtDistance(const float d);
	XMFLOAT3 GetForward();
	XMFLOAT3 GetRight();
	XMFLOAT3 GetUp();
	
	~SplineMesh();

protected:
	void initBuffers(ID3D11Device* device);

private:
	SL::CRSplineController* spline_controller_;
	XMFLOAT3 forward_;
	XMFLOAT3 right_;
	XMFLOAT3 up_;
	int resolution_;

};