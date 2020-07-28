
#include "App1.h"
#include "TrackMesh.h"

App1::App1()
{
	line_controller_ = nullptr;
	spline_ = nullptr;
	track_ = nullptr;
	application_state_ = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	textureMgr->loadTexture("default", L"../res/DefaultDiffuse.png");
	textureMgr->loadTexture("rock", L"../res/rock_texture.png");

	// Create Mesh objects
	SplineMesh* spline_mesh = new SplineMesh(renderer->getDevice(), renderer->getDeviceContext(), 1000);
	PlaneMesh* plane_mesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	CubeMesh* cube_mesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	//PipeMesh* pipe_mesh = new PipeMesh(renderer->getDevice(), renderer->getDeviceContext(), 0.1f);

	//	Create Shader objects.
	ColourShader* colour_shader = new ColourShader(renderer->getDevice(), hwnd);
	DefaultShader* default_shader = new DefaultShader(renderer->getDevice(), hwnd);


	//	Create Mesh instances and assign shaders.
	MeshInstance* plane = new MeshInstance(textureMgr->getTexture("default"), default_shader, plane_mesh);
	if (plane)
	{
		XMMATRIX translation_matrix, scale_matrix;
		scale_matrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
		translation_matrix = XMMatrixTranslation(0.0f, -2.0f, 0.0f);
		plane->SetWorldMatrix(scale_matrix * translation_matrix * renderer->getWorldMatrix());
		objects_.push_back(plane);
	}

	spline_ = new MeshInstance(colour_shader, spline_mesh);
	if (spline_)
	{
		//spline_->SetScaleMatrix(XMFLOAT3(1.0f, 1.0f, 1.0f));
		objects_.push_back(spline_);
	}

	//MeshInstance* pipe = new MeshInstance(textureMgr->getTexture("rock"), colour_shader, pipe_mesh);
	//if (pipe)
	//{
	//	objects_.push_back(pipe);
	//}
	TrackMesh* track_mesh = new TrackMesh(renderer->getDevice(), renderer->getDeviceContext(), colour_shader);

	for (int i = 0; i < track_mesh->GetInstanceCount(); i++)
	{
		objects_.push_back(track_mesh->GetMeshInstance(i));
	}

	line_controller_ = new LineController(renderer->getDevice(), renderer->getDeviceContext(), colour_shader, 6);

	camera = &default_camera_;
	camera->setPosition(0.0f, 0.0f, -10.0f);
	camera->update();


	track_ = new Track(1000, spline_mesh, track_mesh);

	//Initialise Application States:
	building_state_.Init(track_);
	simulating_state_.Init(track_);
	simulating_state_.SetLineController(line_controller_);
	application_state_ = &building_state_;

	//renderer->setWireframeMode(true);
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	//	Clean up.
	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i])
		{
			delete objects_[i];
			objects_[i] = 0;
		}
	}

	if (line_controller_)
	{
		delete line_controller_;
		line_controller_ = 0;
	}

	if (track_)
	{
		delete track_;
		track_ = 0;
	}
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}

	if (application_state_)
	{
		if (application_state_->Exit())
		{
			SwitchApplicationState(application_state_->OnExit());
		}

		application_state_->Update(timer->getTime());
	}

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	
	return true;
}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	//// Clear the scene. (default blue colour)
	renderer->beginScene(0.6f, 0.6f, 0.6f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	camera->update();

	//// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	//	Render all mesh instances.
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_.at(i)->Render(renderer->getDeviceContext(), viewMatrix, projectionMatrix);
	}

	line_controller_->Render(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);

	// Render GUI
	gui();

	//// Present the rendered scene to the screen.
	renderer->endScene();

	return true;
}

void App1::SwitchApplicationState(ApplicationState::APPLICATIONSTATE state)
{
	switch (state)
	{
	case ApplicationState::APPLICATIONSTATE::BUILDING_STATE:
		application_state_ = &building_state_;
		break;

	case ApplicationState::APPLICATIONSTATE::SIMULATING_STATE:
		application_state_ = &simulating_state_;
		break;
	}
}

void App1::gui()
{
	// Force turn off on Geometry shader
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());

	application_state_->RenderUI();

	// Render UI
	ImGui::Render();
}

