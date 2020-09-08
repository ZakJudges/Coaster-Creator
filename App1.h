// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "ColourShader.h"//
#include "../DXFramework/Geometry.h"//
//#include "SplineMesh.h"//
#include "DefaultShader.h"//
#include "MeshInstance.h"
#include <vector>
#include "CoasterCamera.h"

#include "Track.h"

#include "BuildingState.h"
#include "SimulatingState.h"

#include "LineController.h"

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
	void SwitchApplicationState(ApplicationState::APPLICATIONSTATE);
	void StateInput();

private:
	LineController* line_controller_;
	std::vector<MeshInstance*> objects_;
	MeshInstance* spline_;

	Track* track_;

	Camera default_camera_;
	CoasterCamera coaster_camera_;

	ApplicationState* application_state_;
	BuildingState building_state_;
	SimulatingState simulating_state_;

	bool wireframe_;
};

#endif