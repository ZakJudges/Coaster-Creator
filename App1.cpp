
#include "App1.h"

App1::App1()
{
	spline_mesh_ = nullptr;
	spline_ = nullptr;
	cube_ = nullptr;
	follow_ = false;
	follow_last_frame_ = false;
	t_ = 0.0f;
	add_segment_ = false;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	textureMgr->loadTexture("default", L"../res/DefaultDiffuse.png");
	textureMgr->loadTexture("rock", L"../res/rock_texture.png");

	// Create Mesh objects
	spline_mesh_ = new SplineMesh(renderer->getDevice(), renderer->getDeviceContext(), 1000);
	PlaneMesh* plane_mesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	CubeMesh* cube_mesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	
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

	spline_ = new MeshInstance(colour_shader, spline_mesh_);
	if (spline_)
	{
		//spline_->SetScaleMatrix(XMFLOAT3(1.0f, 1.0f, 1.0f));
		objects_.push_back(spline_);
	}

	track_ = new Track(1000, spline_mesh_);

	//cube_ = new MeshInstance(textureMgr->getTexture("rock"), default_shader, cube_mesh);
	//if (cube_)
	//{
	//objects_.push_back(cube_);
	//}

	line_controller_ = new LineController(renderer->getDevice(), renderer->getDeviceContext(), colour_shader, 6);

	camera = &default_camera_;
	camera->setPosition(0.0f, 0.0f, -10.0f);
	camera->update();


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

	if (spline_mesh_)
	{
		delete spline_mesh_;
		spline_mesh_ = 0;
	}

	if (line_controller_)
	{
		delete line_controller_;
		line_controller_ = 0;
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

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	if (follow_last_frame_ != follow_)
	{
		if (follow_)
		{
			//input->DeactivateInput();
			//t_ = 0.0f;
			//camera = &coaster_camera_;
		}
		else
		{
			//input->ActivateInput();
			//t_ = 0.0f;
			//camera = &default_camera_;
		}
	}
	follow_last_frame_ = follow_;

	if (follow_)
	{
		if (t_ <= 1.0f)
		{
			//line_controller_->Clear();
			////	Build the transform for the object travelling along the spline.
			//XMFLOAT3 position = spline_mesh_->GetPointAtDistance(t_);
			//XMVECTOR pos = DirectX::XMVectorSet(position.x, position.y, position.z, 1.0f);
			//pos = XMVector3Transform(pos, spline_->GetWorldMatrix());
			//
			////	Calculate camera axes of rotation.
			//XMFLOAT3 start = XMFLOAT3(XMVectorGetX(pos), XMVectorGetY(pos), XMVectorGetZ(pos));
			//XMFLOAT3 forward = spline_mesh_->GetForward();
			//XMFLOAT3 end(start.x + forward.x, start.y + forward.y , start.z + forward.z);
			//line_controller_->AddLine(start, end, XMFLOAT3(1.0f, 0.0f, 0.0f));
			//
			//XMFLOAT3 right = spline_mesh_->GetRight();
			//end = XMFLOAT3(start.x + right.x, start.y + right.y, start.z + right.z);
			//line_controller_->AddLine(start, end, XMFLOAT3(0.0f, 0.0f, 1.0f));

			//XMFLOAT3 up = spline_mesh_->GetUp();
			//end = XMFLOAT3(start.x + up.x, start.y + up.y, start.z + up.z);
			//line_controller_->AddLine(start, end, XMFLOAT3(0.0f, 1.0f, 0.0f));
			//		
			//t_ += (0.1f * timer->getTime());
		}
		else if (t_ > 1.0f)
		{
			t_ = 0.0f;
		}
	}

	if (add_segment_)
	{
		add_segment_ = false;
		track_->AddTrackPiece(TrackPiece::Tag::STRAIGHT);
		
	}
	return true;
}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	//// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

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

void App1::gui()
{
	// Force turn off on Geometry shader
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Follow Path", &follow_);
	ImGui::Checkbox("Add Segment", &add_segment_);

	// Render UI
	ImGui::Render();
}

