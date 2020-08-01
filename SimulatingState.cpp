#include "SimulatingState.h"

SimulatingState::SimulatingState()
{
	t_ = 0.0f;
	track_ = nullptr;
	line_controller_ = nullptr;
}

void SimulatingState::Init(void* ptr)
{
	track_ = static_cast<Track*>(ptr);
}

void SimulatingState::Update(float delta_time)
{
	t_ += (0.05f * delta_time);

	if (t_ > 1.0f || t_ < 0.0f)
	{
		t_ = 0.0f;
		track_->Reset();
	}

	track_->Update(t_);

	AddLines();
}

void SimulatingState::AddLines()
{
	if (line_controller_)
	{
		line_controller_->Clear();

		//	Build the transform for the object travelling along the spline.
		//XMFLOAT3 start = track_->GetPointAtDistance(t_);
		XMFLOAT3 start = track_->GetPoint();

		XMFLOAT3 forward = track_->GetForward();
		XMFLOAT3 end(start.x + forward.x, start.y + forward.y, start.z + forward.z);
		line_controller_->AddLine(start, end, XMFLOAT3(1.0f, 0.0f, 0.0f));

		XMFLOAT3 right = track_->GetRight();
		end = XMFLOAT3(start.x + right.x, start.y + right.y, start.z + right.z);
		line_controller_->AddLine(start, end, XMFLOAT3(0.0f, 0.0f, 1.0f));

		XMFLOAT3 up = track_->GetUp();
		end = XMFLOAT3(start.x + up.x, start.y + up.y, start.z + up.z);
		line_controller_->AddLine(start, end, XMFLOAT3(0.0f, 1.0f, 0.0f));
	}
}

void SimulatingState::RenderUI()
{
	ImGui::Text("Simulating State");
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Build", &exit_);
}
void SimulatingState::SetLineController(LineController* line_controller)
{
	line_controller_ = line_controller;
}

void SimulatingState::OnEnter()
{
	track_->SetSimulatingState();
}

ApplicationState::APPLICATIONSTATE SimulatingState::OnExit()
{
	exit_ = false;

	return APPLICATIONSTATE::BUILDING_STATE;
}

SimulatingState::~SimulatingState()
{

}

