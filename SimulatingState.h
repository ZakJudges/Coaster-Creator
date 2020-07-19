#pragma once

#include "ApplicationState.h"
#include "Track.h"

class SimulatingState : public ApplicationState
{
public:
	SimulatingState();
	void Init(void* ptr);
	void Update(float delta_time);
	void RenderUI();
	~SimulatingState();

private:
	float t_;
	Track* track_;

};