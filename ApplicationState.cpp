#include "ApplicationState.h"


//	static application state settings.
bool ApplicationState::wireframe_state_ = false;
bool ApplicationState::application_running_ = true;
bool ApplicationState::show_fps_ = false;
int ApplicationState::screen_width_ = 0;



//	Common variables accross all application states.
ApplicationState::ApplicationState()
{
	exit_ = false;
	in_focus_ = true;
	line_controller_ = nullptr;
}

bool ApplicationState::ShowFPS()
{
	return show_fps_;
}

void ApplicationState::ToggleFPS()
{
	show_fps_ = !show_fps_;
}

bool ApplicationState::GetWireframeState()
{
	return wireframe_state_;
}

void ApplicationState::SetWireframeState(bool state)
{
	wireframe_state_ = state;
}

void ApplicationState::SetScreenWidth(int screen_width)
{
	screen_width_ = screen_width;
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

//	Returns true when current state is in focus.
bool ApplicationState::GetFocus()
{
	return in_focus_;
}

//	Empty functions for the keyboard input. These are not pure virtual so that if a state does not require any input,
//		it does not need to implement the functions.
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


