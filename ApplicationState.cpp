#include "ApplicationState.h"

ApplicationState::ApplicationState()
{
	exit_ = false;
	in_focus_ = true;
}

ApplicationState::~ApplicationState()
{

}

bool ApplicationState::Exit()
{
	return exit_;
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



