#pragma once

#include <DirectXMath.h>
#include "ColourShader.h"
#include "LineMesh.h"

class LineController
{
public:
	LineController(ID3D11Device* device, ID3D11DeviceContext* device_context, ColourShader* colour_shader_, const unsigned int max_vertices);
	void AddLine(XMFLOAT3 start, XMFLOAT3 end, XMFLOAT3 colour);
	void Clear();
	void Render(ID3D11DeviceContext* device_context, XMMATRIX& world, XMMATRIX& view, XMMATRIX& projection);
	void SetRenderFlag(bool render);
	bool GetRenderFlag();

	~LineController();
private:
	LineMesh* line_mesh_;
	ColourShader* colour_shader_;
	bool should_render_;
	
};