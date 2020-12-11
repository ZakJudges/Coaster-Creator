#include "ApplicationState.h"

ApplicationState::ApplicationState()
{
	exit_ = false;
	in_focus_ = true;
	application_running_ = true;
	wireframe_state_ = false;
	line_controller_ = nullptr;
}

bool ApplicationState::GetWireframeState()
{
	return wireframe_state_;
}

void ApplicationState::SetWireframeState(bool state)
{
	wireframe_state_ = state;
}

ApplicationState::~ApplicationState()
{
	
}

bool ApplicationState::Exit()
{
	return exit_;
}

bool ApplicationState::ApplicationRunning()
{
	return application_running_;
}

void ApplicationState::SetCameraLookAt(float x, float y, float z)
{
}

//	Return true if current state is in focus.
bool ApplicationState::GetFocus()
{
	return in_focus_;
}

void ApplicationState::OnWPress()
{
}

void ApplicationState::OnSPress()
{
}

void ApplicationState::OnDPress()
{
}

void ApplicationState::OnAPress()
{
}

void ApplicationState::OnEPress()
{
}

void ApplicationState::OnQPress()
{
}

void ApplicationState::SetLineController(LineController* line_controller)
{
	line_controller_ = line_controller;
}

LineController* ApplicationState::GetLineController()
{
	return line_controller_;
}


