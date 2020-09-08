#include "BuildingState.h"

BuildingState::BuildingState()
{
	track_ = nullptr;
	track_builder_ = nullptr;
	generate_mesh_ = false;
	delta_time_ = 0.0f;

	move_speed_ = 5.0f;
}

void BuildingState::Init(void* ptr)
{
	track_ = static_cast<Track*>(ptr);
	
	track_builder_ = new TrackBuilder(track_);
}

void BuildingState::Update(float delta_time)
{

	delta_time_ = delta_time;

	if (track_builder_->UpdateTrack())
	{
		track_->UpdateBuildingMesh();
		generate_mesh_ = true;
	}

	if (generate_mesh_)
	{
		//track_->GenerateMesh();
		track_builder_->UpdatePreviewMesh();
		generate_mesh_ = false;
	}
}

void BuildingState::RenderUI()
{
	bool test = false;
	ImGui::Text("Building State");

	//	Adding new track pieces.
	ImGui::Checkbox("Editing Track Piece", track_builder_->SetPreviewActive());
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
	

	float p0[3] = { track_builder_->GetP0('x'), track_builder_->GetP0('y'), track_builder_->GetP0('z') };
	float p1[3] = { track_builder_->GetP1('x'), track_builder_->GetP1('y'), track_builder_->GetP1('z') };
	float p2[3] = { track_builder_->GetP2('x'), track_builder_->GetP2('y'), track_builder_->GetP2('z') };
	float p3[3] = { track_builder_->GetP3('x'), track_builder_->GetP3('y'), track_builder_->GetP3('z') };

	//float p0_lim = p0[0] + p0[1] + p0[2];

	ImGui::Begin("Track Piece Attributes");
	ImGui::Checkbox("P0", track_builder_->SetActiveControlPoint(0));
	ImGui::Checkbox("P1", track_builder_->SetActiveControlPoint(1));
	ImGui::Checkbox("P2", track_builder_->SetActiveControlPoint(2));
	ImGui::Checkbox("P3", track_builder_->SetActiveControlPoint(3));

	ImGui::SliderInt("Roll Target:", track_builder_->SetRollTarget(), -720, 720);
	ImGui::SliderFloat3("P0", p0, -100, 100, "%.3f", 1.0f);
	ImGui::SliderFloat3("P1", p1, -100, 100, "%.3f", 1.0f);
	ImGui::SliderFloat3("P2", p2, -100, 100, "%.3f", 1.0f);
	ImGui::SliderFloat3("P3", p3, -100, 100, "%.3f", 1.0f);

	//track_builder_->SetP0('x', p0[0]); 	track_builder_->SetP0('y', p0[1]);	track_builder_->SetP0('z', p0[2]);
	//track_builder_->SetP1('x', p1[0]); 	track_builder_->SetP1('y', p1[1]);	track_builder_->SetP1('z', p1[2]);
	//track_builder_->SetP2('x', p2[0]); 	track_builder_->SetP2('y', p2[1]);	track_builder_->SetP2('z', p2[2]);
	//track_builder_->SetP3('x', p3[0]); 	track_builder_->SetP3('y', p3[1]);	track_builder_->SetP3('z', p3[2]);

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

void BuildingState::OnTPress()
{
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			// Increase z value of all active control points.
			track_builder_->SetControlPoint(i, 'z', track_builder_->GetControlPoint(i, 'z') + (move_speed_ * delta_time_));
		}
	}
}

void BuildingState::OnGPress()
{
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			// Increase z value of all active control points.
			track_builder_->SetControlPoint(i, 'z', track_builder_->GetControlPoint(i, 'z') - (move_speed_ * delta_time_));
		}
	}
}

void BuildingState::OnHPress()
{
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			// Increase z value of all active control points.
			track_builder_->SetControlPoint(i, 'x', track_builder_->GetControlPoint(i, 'x') + (move_speed_ * delta_time_));
		}
	}
}

void BuildingState::OnFPress()
{
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			// Increase z value of all active control points.
			track_builder_->SetControlPoint(i, 'x', track_builder_->GetControlPoint(i, 'x') - (move_speed_ * delta_time_));
		}
	}
}

void BuildingState::OnYPress()
{
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			// Increase z value of all active control points.
			track_builder_->SetControlPoint(i, 'y', track_builder_->GetControlPoint(i, 'y') + (move_speed_ * delta_time_));
		}
	}
}

void BuildingState::OnRPress()
{
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			// Increase z value of all active control points.
			track_builder_->SetControlPoint(i, 'y', track_builder_->GetControlPoint(i, 'y') - (move_speed_ * delta_time_));
		}
	}
}
