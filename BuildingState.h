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
	APPLICATIONSTATE OnExit();
	~BuildingState();

private:
	TrackBuilder* track_builder_;
	Track* track_;
};