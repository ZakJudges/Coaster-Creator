#include "SimulatingState.h"

SimulatingState::SimulatingState()
{
	t_ = 0.0f;
	track_ = nullptr;
}

void SimulatingState::Init(void* ptr)
{
	track_ = static_cast<Track*>(ptr);
}

void SimulatingState::Update(float delta_time)
{
	t_ += (0.05f * delta_time);

	if (t_ >= 1.0f || t_ < 0.0f)
	{
		t_ = 0.0f;
	}

	track_->Update(t_);
}

void SimulatingState::RenderUI()
{
	ImGui::Text("Simulating State");
}

SimulatingState::~SimulatingState()
{

}

