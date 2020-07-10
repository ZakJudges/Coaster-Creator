
#include "App1.h"

App1::App1()
{
	line_controller_ = nullptr;
	spline_ = nullptr;
	cube_ = nullptr;
	follow_ = false;
	follow_last_frame_ = false;
	t_ = 0.0f;
	track_builder_ = nullptr;
	track_ = nullptr;
}



void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	textureMgr->loadTexture("default", L"../res/DefaultDiffuse.png");
	textureMgr->loadTexture("rock", L"../res/rock_texture.png");

	// Create Mesh objects
	SplineMesh* spline_mesh = new SplineMesh(renderer->getDevice(), renderer->getDeviceContext(), 3000);
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

	spline_ = new MeshInstance(colour_shader, spline_mesh);
	if (spline_)
	{
		//spline_->SetScaleMatrix(XMFLOAT3(1.0f, 1.0f, 1.0f));
		objects_.push_back(spline_);
	}

	track_ = new Track(3000, spline_mesh);

	//cube_ = new MeshInstance(textureMgr->getTexture("rock"), default_shader, cube_mesh);
	//if (cube_)
	//{
	//objects_.push_back(cube_);
	//}

	line_controller_ = new LineController(renderer->getDevice(), renderer->getDeviceContext(), colour_shader, 6);

	camera = &default_camera_;
	camera->setPosition(0.0f, 0.0f, -10.0f);
	camera->update();

	track_builder_ = new TrackBuilder(track_);
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

	if (track_builder_)
	{
		delete track_builder_;
		track_builder_ = 0;
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
		line_controller_->Clear();
		//	Build the transform for the object travelling along the spline.
		XMVECTOR position = track_->GetPointAtTime(t_);
		//position = XMVector3Transform(position, spline_->GetWorldMatrix());

		//	Calculate camera axes of rotation.
		XMFLOAT3 start = XMFLOAT3(XMVectorGetX(position), XMVectorGetY(position), XMVectorGetZ(position));
		XMFLOAT3 forward = track_->GetForward(t_);
		XMFLOAT3 end(start.x + forward.x, start.y + forward.y, start.z + forward.z);
		line_controller_->AddLine(start, end, XMFLOAT3(1.0f, 0.0f, 0.0f));

		XMFLOAT3 right = track_->GetRight(t_);
		end = XMFLOAT3(start.x + right.x, start.y + right.y, start.z + right.z);
		line_controller_->AddLine(start, end, XMFLOAT3(0.0f, 0.0f, 1.0f));

		XMFLOAT3 up = track_->GetUp(t_);
		end = XMFLOAT3(start.x + up.x, start.y + up.y, start.z + up.z);
		line_controller_->AddLine(start, end, XMFLOAT3(0.0f, 1.0f, 0.0f));

		t_ += (0.02f * timer->getTime());

		if (t_ >= 1.0f || t_ < 0.0f)
		{
			t_ = 0.0f;
		}
	}
	
	track_builder_->UpdateTrack();

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
void App1::gui()
{
	// Force turn off on Geometry shader
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Text("Track Piece Type");
	ImGui::Spacing();
	ImGui::Checkbox("Add Straight", track_builder_->SetTrackPieceType(TrackPiece::Tag::STRAIGHT));
	ImGui::Checkbox("Add Right Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::RIGHT_TURN));
	ImGui::Checkbox("Add Left Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::LEFT_TURN));
	ImGui::Checkbox("Add Climb Up", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_UP));
	ImGui::Checkbox("Add Climb Down", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_DOWN));
	ImGui::Checkbox("Add Loop", track_builder_->SetTrackPieceType(TrackPiece::Tag::LOOP));
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Complete Track", track_builder_->SetTrackPieceType(TrackPiece::Tag::COMPLETE_TRACK));
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Undo", track_builder_->SetTrackPieceType(TrackPiece::Tag::UNDO));
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Follow Path", &follow_);

	// Render UI
	ImGui::Render();
}

