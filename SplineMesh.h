#pragma once

#include "../DXFramework/BaseMesh.h"
#include "../Splines/CRSplineController.h"
#include "Track.h"

class SplineMesh : public BaseMesh
{
public:
	SplineMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution);
	void sendData(ID3D11DeviceContext* deviceContext);

	void Update(SL::CRSplineController* spline_controller);

	XMFLOAT3 GetPointAtDistance(const float d);

	
	~SplineMesh();

protected:
	void initBuffers(ID3D11Device* device);
	void UpdateVertexBuffer();

private:
	//SL::CRSplineController* spline_controller_;
	Track* track_;

	int resolution_;
	ID3D11Device* device_;
	ID3D11DeviceContext* device_context_;

};