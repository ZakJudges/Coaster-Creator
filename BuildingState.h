#pragma once

#include "ApplicationState.h"

#include "TrackBuilder.h"
#include "Track.h"

class TrackLoader;

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

	// Input.
	virtual void OnWPress();
	virtual void OnSPress();
	virtual void OnDPress();
	virtual void OnAPress();
	virtual void OnEPress();
	virtual void OnQPress();

private:
	TrackBuilder* track_builder_;
	Track* track_;
	float delta_time_;
	float move_speed_;

	TrackLoader* track_loader_;

	char buffer_[64];

	

	float p0_[3];
	float p1_[3];
	float p2_[3];
	float p3_[3];
};