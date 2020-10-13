#include "BuildingState.h"

#include "TrackLoader.h"

BuildingState::BuildingState()
{
	track_ = nullptr;
	track_builder_ = nullptr;
	track_loader_ = nullptr;
	delta_time_ = 0.0f;

	//	Initialise the file name buffer.
	static char const buffer[] = ".txt";
	strcpy_s(buffer_, buffer);
	
	move_speed_ = 5.0f;
}

void BuildingState::Init(void* ptr)
{
	track_ = static_cast<Track*>(ptr);
	
	track_builder_ = new TrackBuilder(track_);

	track_loader_ = new TrackLoader();
}

void BuildingState::Update(float delta_time)
{
	delta_time_ = delta_time;

	track_builder_->UpdateTrack();
}

void BuildingState::RenderUI()
{
	//ImGui::Text("Building State");
	//	Adding new track pieces.
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			in_focus_ = false;
			if (ImGui::SmallButton("Erase Track"))
			{
			}
			ImGui::Spacing();
			ImGui::Separator();
			if (ImGui::BeginMenu("Save As"))
			{

				ImGui::InputText("File Name", buffer_, sizeof(buffer_));
			
				if (ImGui::Button("Save"))
				{
					//	Save the track to file.
					if (track_loader_->SaveTrack(buffer_, track_))
					{
						
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Load"))
			{
				ImGui::InputText("File Name", buffer_, sizeof(buffer_));
				if (ImGui::Button("Load"))
				{
					//	Load the track from the file.
					if (track_loader_->LoadTrack(buffer_, track_))
					{

					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		else
		{
			in_focus_ = true;
		}
		ImGui::Indent(982.0f);
		if (ImGui::Button("Exit"))
		{
			application_running_ = false;
		}
		ImGui::EndMainMenuBar();
	}
	
	ImGui::Separator();
	
	ImGui::Text("Track Piece Type");
	ImGui::Checkbox("Add Straight", track_builder_->SetTrackPieceType(TrackPiece::Tag::STRAIGHT));
	ImGui::Checkbox("Add Right Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::RIGHT_TURN));
	ImGui::Checkbox("Add Left Turn", track_builder_->SetTrackPieceType(TrackPiece::Tag::LEFT_TURN));
	ImGui::Checkbox("Add Climb Up", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_UP));
	ImGui::Checkbox("Add Climb Down", track_builder_->SetTrackPieceType(TrackPiece::Tag::CLIMB_DOWN));
	ImGui::Checkbox("Join Track", track_builder_->SetTrackPieceType(TrackPiece::Tag::COMPLETE_TRACK));
	ImGui::Checkbox("Undo", track_builder_->SetUndo());
	ImGui::Spacing();
	ImGui::Checkbox("Finish Track Piece", track_builder_->SetPreviewFinished());
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Simulate", &exit_);

	ImGui::Begin("Track Piece Attributes");
	ImGui::Checkbox("P0", track_builder_->SetActiveControlPoint(0));
	ImGui::Checkbox("P1", track_builder_->SetActiveControlPoint(1));
	ImGui::Checkbox("P2", track_builder_->SetActiveControlPoint(2));
	ImGui::Checkbox("P3", track_builder_->SetActiveControlPoint(3));

	ImGui::SliderInt("Roll Target:", track_builder_->SetRollTarget(), -720, 720);

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

	if (track_loader_)
	{
		delete track_loader_;
		track_loader_ = 0;
	}
}

void BuildingState::OnWPress()
{
	//	Move all active control points forward.
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			SL::Vector new_pos = camera_look_at_;
			new_pos.SetY(0.0f);
			new_pos.Scale(move_speed_ * delta_time_);
			new_pos = track_builder_->GetControlPoint(i).Add(new_pos);

			track_builder_->SetControlPoint(i, new_pos);
		}
	}
}

void BuildingState::OnSPress()
{
	//	Move all active control points backwards.
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			SL::Vector new_pos = camera_look_at_;
			new_pos.SetY(0.0f);
			new_pos.Scale(move_speed_ * delta_time_);
			new_pos = track_builder_->GetControlPoint(i).Subtract(new_pos);

			track_builder_->SetControlPoint(i, new_pos);
		}
	}
}

void BuildingState::OnDPress()
{
	//	Move all active control points to the right.
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			SL::Vector up(0.0f, 1.0f, 0.0f);
			SL::Vector new_pos = camera_look_at_.Cross(up);
			new_pos.SetY(0.0f);
			new_pos.Scale(move_speed_ * delta_time_);
			new_pos = track_builder_->GetControlPoint(i).Subtract(new_pos);

			track_builder_->SetControlPoint(i, new_pos);
		}
	}
}

void BuildingState::OnAPress()
{
	//	Move all active control points to the left.
	for (int i = 0; i < 4; i++)
	{
		if (track_builder_->GetActiveControlPoint(i))
		{
			SL::Vector up(0.0f, 1.0f, 0.0f);
			SL::Vector new_pos = camera_look_at_.Cross(up);
			new_pos.SetY(0.0f);
			new_pos.Scale(move_speed_ * delta_time_);
			new_pos = track_builder_->GetControlPoint(i).Add(new_pos);

			track_builder_->SetControlPoint(i, new_pos);
		}
	}
}

void BuildingState::OnEPress()
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

void BuildingState::OnQPress()
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

void BuildingState::SetCameraLookAt(float x, float y, float z)
{
	camera_look_at_.Set(x, y, z);
}
