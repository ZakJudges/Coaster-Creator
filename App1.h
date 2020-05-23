// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "ColourShader.h"//
#include "../DXFramework/Geometry.h"//
#include "SplineMesh.h"//
#include "DefaultShader.h"//
#include "MeshInstance.h"
#include <vector>

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in);

	bool frame();

protected:
	bool render();
	void gui();

private:
	std::vector<MeshInstance*> objects_;
	SplineMesh* spline_mesh_;

	//	ImGui:
	bool follow_;
	bool follow_last_frame_;

	//	Spline:
	float t_;

	
};

#endif