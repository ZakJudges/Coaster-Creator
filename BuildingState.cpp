#include "BuildingState.h"

BuildingState::BuildingState()
{
	track_ = nullptr;
	track_builder_ = nullptr;
	generate_mesh_ = false;
	roll_target_ = 0.0f;
}

void BuildingState::Init(void* ptr)
{
	track_ = static_cast<Track*>(ptr);
	
	track_builder_ = new TrackBuilder(track_);
}

void BuildingState::Update(float delta_time)
{
	//if(user changed track piece)
	//{
	//	*Fill the user-generated track piece with the new data*
	//	track_->UpdateBuildingMesh();
	//}
		// After altering control points:
//	old length = spline_controller__>GetArcLength();
//	new length = spline_controller_->CalculateSplineLength().
//	diff = new length - old length
//	track_piece->SetLength(track_piece->GetLength()+diff);
	if (track_builder_->UpdateTrack())
	{
		
	}

	if (generate_mesh_)
	{
		track_->GenerateMesh();
		generate_mesh_ = false;
	}
}

void BuildingState::RenderUI()
{
	bool test = false;
	ImGui::Text("Building State");

	//	Adding new track pieces.
	ImGui::Text("Track Piece Type");
	ImGui::Spacing();
	ImGui::Checkbox("Add Straight", track_builder_->SetTrackPieceType(TrackPiece::Tag::STRAIGHT));
	ImGui::Checkbox("Add Right Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::RIGHT_TURN));
	ImGui::Checkbox("Add Left Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::LEFT_TURN));
	ImGui::Checkbox("Add Climb Up", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_UP));
	ImGui::Checkbox("Add Climb Down", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_DOWN));
	ImGui::Checkbox("Add Loop", track_builder_->SetTrackPieceType(TrackPiece::Tag::LOOP));
	ImGui::Checkbox("Add Custom Track Piece", track_builder_->SetTrackPieceType(TrackPiece::Tag::USER_GENERATED));
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
	ImGui::Checkbox("Generate Mesh", &generate_mesh_);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Simulate", &exit_);

	//	Altering new track pieces.
	ImGui::Begin("Track Piece Attributes");
	ImGui::SliderInt("Roll Target:", track_builder_->SetRollTarget(), -90, 90);
	ImGui::End();
}

void BuildingState::OnEnter()
{
	track_->SetBuildingState();
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
