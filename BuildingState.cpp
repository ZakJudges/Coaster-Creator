#include "BuildingState.h"

BuildingState::BuildingState()
{
	track_ = nullptr;
	track_builder_ = nullptr;
}

void BuildingState::Init(void* ptr)
{
	track_ = static_cast<Track*>(ptr);
	
	track_builder_ = new TrackBuilder(track_);
}

void BuildingState::Update(float delta_time)
{
	track_builder_->UpdateTrack();
}

void BuildingState::RenderUI()
{
	ImGui::Text("Building State");

	ImGui::Text("Track Piece Type");
	ImGui::Spacing();
	ImGui::Checkbox("Add Straight", track_builder_->SetTrackPieceType(TrackPiece::Tag::STRAIGHT));
	ImGui::Checkbox("Add Right Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::RIGHT_TURN));
	ImGui::Checkbox("Add Left Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::LEFT_TURN));
	ImGui::Checkbox("Add Climb Up", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_UP));
	ImGui::Checkbox("Add Climb Down", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_DOWN));
	ImGui::Checkbox("Add Loop", track_builder_->SetTrackPieceType(TrackPiece::Tag::LOOP));
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Complete Track", track_builder_->SetTrackPieceType(TrackPiece::Tag::COMPLETE_TRACK));
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Undo", track_builder_->SetTrackPieceType(TrackPiece::Tag::UNDO));
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Simulate", &exit_);
}

ApplicationState::APPLICATIONSTATE BuildingState::OnExit()
{
	exit_ = false;

	return APPLICATIONSTATE::SIMULATING_STATE;
}

BuildingState::~BuildingState()
{
	if (track_builder_)
	{
		delete track_builder_;
		track_builder_ = 0;
	}
}
