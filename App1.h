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
	ColourShader* colourShader;
	DefaultShader* default_shader_;
	SplineMesh* spline_mesh_;
	PlaneMesh* plane_mesh_;
	MeshInstance* plane_;

	
};

#endif