#pragma once

#include "ApplicationState.h"
#include "Track.h"

#include "LineController.h"

class SimulatingState : public ApplicationState
{
public:
	SimulatingState();
	void Init(void* ptr);
	void Update(float delta_time);
	void RenderUI();
	APPLICATIONSTATE OnExit();
	void SetLineController(LineController* line_controller);
	~SimulatingState();

private:
	void AddLines();

private:
	LineController* line_controller_;
	float t_;
	Track* track_;

};