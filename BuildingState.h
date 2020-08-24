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

	// Input.
	virtual void OnTPress();
	virtual void OnGPress();
	virtual void OnHPress();
	virtual void OnFPress();
	virtual void OnYPress();
	virtual void OnRPress();

private:
	TrackBuilder* track_builder_;
	Track* track_;
	bool generate_mesh_;
	float delta_time_;
	float move_speed_;

	float p0_[3];
	float p1_[3];
	float p2_[3];
	float p3_[3];
};