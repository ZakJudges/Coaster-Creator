
#include "App1.h"

App1::App1()
{
	spline_mesh_ = nullptr;
	colourShader = nullptr;
	default_shader_ = nullptr;
	plane_mesh_ = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	textureMgr->loadTexture("default", L"../res/DefaultDiffuse.png");


	// Create Mesh objects
	spline_mesh_ = new SplineMesh(renderer->getDevice(), renderer->getDeviceContext(), "points.txt");
	plane_mesh_ = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());

	//	Create Shader objects.
	colourShader = new ColourShader(renderer->getDevice(), hwnd);
	default_shader_ = new DefaultShader(renderer->getDevice(), hwnd);

	plane_ = new MeshInstance(textureMgr->getTexture("default"), default_shader_, plane_mesh_);

}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (spline_mesh_)
	{
		delete spline_mesh_;
		spline_mesh_ = 0;
	}

	if (plane_mesh_)
	{
		delete plane_mesh_;
		plane_mesh_ = 0;
	}

	if (colourShader)
	{
		delete colourShader;
		colourShader = 0;
	}

	if (default_shader_)
	{
		delete default_shader_;
		default_shader_ = 0;
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

	//	Render default shader meshes.
	default_shader_->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	plane_mesh_->sendData(renderer->getDeviceContext());
	default_shader_->render(renderer->getDeviceContext(), plane_mesh_->getIndexCount());

	//	Render colour shader meshes
	colourShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	spline_mesh_->sendData(renderer->getDeviceContext());
	colourShader->render(renderer->getDeviceContext(), spline_mesh_->getIndexCount());

	





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

	// Render UI
	ImGui::Render();
}

