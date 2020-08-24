#pragma once

#include "ApplicationState.h"

#include "TrackBuilder.h"
#include "Track.h"

class BuildingState : public ApplicationState
{
public:
	BuildingState();
	void Init(void* ptr);
	void Update(float delta_time);
	void RenderUI();
	void OnEnter();
	APPLICATIONSTATE OnExit();
	~BuildingState();

private:
	TrackBuilder* track_builder_;
	Track* track_;
	bool generate_mesh_;
	int roll_target_;

};