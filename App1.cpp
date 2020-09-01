
#include "App1.h"
#include "TrackMesh.h"

App1::App1()
{
	line_controller_ = nullptr;
	spline_ = nullptr;
	track_ = nullptr;
	application_state_ = nullptr;
	wireframe_ = false;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	textureMgr->loadTexture("default", L"../res/DefaultDiffuse.png");
	textureMgr->loadTexture("rock", L"../res/rock_texture.png");

	// Create Mesh objects
	//SplineMesh* spline_mesh = new SplineMesh(renderer->getDevice(), renderer->getDeviceContext(), 1000);
	PlaneMesh* plane_mesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	CubeMesh* cube_mesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	//PipeMesh* pipe_mesh = new PipeMesh(renderer->getDevice(), renderer->getDeviceContext(), 0.1f);

	//	Create Shader objects.
	ColourShader* colour_shader = new ColourShader(renderer->getDevice(), hwnd);
	DefaultShader* default_shader = new DefaultShader(renderer->getDevice(), hwnd);


	//	Create Mesh instances and assign shaders.
	MeshInstance* plane = new MeshInstance(textureMgr->getTexture("default"), default_shader , plane_mesh);
	if (plane)
	{
		XMMATRIX translation_matrix, scale_matrix;
		scale_matrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
		translation_matrix = XMMatrixTranslation(0.0f, -2.0f, 0.0f);
		plane->SetWorldMatrix(scale_matrix * translation_matrix * renderer->getWorldMatrix());
		//plane->SetColour(XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
		objects_.push_back(plane);
	}

	/*spline_ = new MeshInstance(colour_shader, spline_mesh);
	if (spline_)
	{
		objects_.push_back(spline_);
		spline_->SetColour(XMFLOAT4(1.0f, 1.0f, 0.2f, 0.0f));
	}*/

	//MeshInstance* pipe = new MeshInstance(textureMgr->getTexture("rock"), colour_shader, pipe_mesh);
	//if (pipe)
	//{
	//	objects_.push_back(pipe);
	//}
	TrackMesh* track_mesh = new TrackMesh(renderer->getDevice(), renderer->getDeviceContext(), colour_shader);

	std::vector<MeshInstance*> track_instances = track_mesh->GetTrackMeshInstances();
	for (int i = 0; i < track_instances.size(); i++)
	{
		objects_.push_back(track_instances[i]);
	}

	line_controller_ = new LineController(renderer->getDevice(), renderer->getDeviceContext(), colour_shader, 6);

	camera = &default_camera_;
	camera->setPosition(0.0f, 0.0f, -10.0f);
	camera->update();


	track_ = new Track(1000, track_mesh);

	//Initialise Application States:
	building_state_.Init(track_);
	simulating_state_.Init(track_);
	simulating_state_.SetLineController(line_controller_);
	application_state_ = &building_state_;
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

		//	Handle application-state-specific input.
		StateInput();

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

	renderer->setWireframeMode(wireframe_);

	//// Clear the scene. (default blue colour)
	renderer->beginScene(0.9f, 0.9f, 0.9f, 1.0f);

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

	application_state_->OnEnter();
}

void App1::StateInput()
{
	
	if (input->isKeyDown(VK_SHIFT))
	{
		if (input->IsActive())
		{
			input->DeactivateInput();
		}
		if (input->isKeyDown('W'))
		{
			application_state_->OnTPress();
		}
		if (input->isKeyDown('S'))
		{
			application_state_->OnGPress();
		}
		if (input->isKeyDown('D'))
		{
			application_state_->OnHPress();
		}
		if (input->isKeyDown('A'))
		{
			application_state_->OnFPress();
		}
		if (input->isKeyDown('E'))
		{
			application_state_->OnYPress();
		}
		if (input->isKeyDown('Q'))
		{
			application_state_->OnRPress();
		}

	}
	else
	{
		if (!input->IsActive())
		{
			input->ActivateInput();
		}
	}
}

void App1::gui()
{
	// Force turn off on Geometry shader
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());

	application_state_->RenderUI();

	ImGui::Checkbox("Wireframe", &wireframe_);

	// Render UI
	ImGui::Render();
}

