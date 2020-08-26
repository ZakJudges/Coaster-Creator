
#pragma once

#include "../DXFramework/BaseMesh.h"
#include <vector>

using namespace DirectX;

class PipeMesh : public BaseMesh
{

public:
	PipeMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float radius);
	void Update();
	void GenerateCircles();		//	TO REMOVE?
	void AddCircleOrigin(XMVECTOR centre, XMVECTOR x_axis, XMVECTOR y_axis);
	void CalculateVertices();
	void CalculateIndices();
	inline void SetSliceCount(int slice_count) { slice_count_ = slice_count; }
	void sendData(ID3D11DeviceContext* deviceContext);
	~PipeMesh();

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;

private:
	struct CircleData
	{
		XMVECTOR centre;
		XMVECTOR x_axis;
		XMVECTOR y_axis;
	};

	ID3D11DeviceContext* device_context_;

	std::vector<VertexType> vertices_;
	unsigned int vertices_element_store_;	//UNUSED
	unsigned int vertices_remove_from_;		//UNUSED

	std::vector<unsigned long int> indices_;
	unsigned int indices_element_store_;	//UNUSED
	unsigned int indices_remove_from_;		//UNUSED

	std::vector<CircleData> circle_data_;

	unsigned int circle_count_;		//TO REMOVE
	unsigned int slice_count_;
	float radius_;
};

