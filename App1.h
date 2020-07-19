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
#include "LineController.h"
#include "CoasterCamera.h"

#include "Track.h"
#include "TrackBuilder.h"

#include "BuildingState.h"
#include "SimulatingState.h"

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
	LineController* line_controller_;
	std::vector<MeshInstance*> objects_;
	MeshInstance* spline_;
	MeshInstance* cube_;

	Track* track_;
	//TrackBuilder* track_builder_;


	Camera default_camera_;
	CoasterCamera coaster_camera_;

	//	ImGui:
	bool follow_;
	bool follow_last_frame_;

	//	Spline:
	float t_;

	SphereMesh* sphere_mesh_;


	ApplicationState* application_state_;
	BuildingState building_state_;
	SimulatingState simulating_state_;


	
};

#endif