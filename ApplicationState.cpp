#include "ApplicationState.h"

ApplicationState::ApplicationState()
{
	exit_ = false;
}

ApplicationState::~ApplicationState()
{

}

bool ApplicationState::Exit()
{
	return exit_;
}

