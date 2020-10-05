#include "TrackBuilder.h"

#include "TrackPreview.h"
#include "RightTurn.h"
#include "Straight.h"
#include "LeftTurn.h"
#include "ClimbUp.h"
#include "ClimbDown.h"
#include "CompleteTrack.h"

TrackBuilder::TrackBuilder(Track* track) : track_(track), track_piece_(nullptr)
{
	//	Size based on total number of different track piece types.
	track_piece_types_ = new TrackPieceType[static_cast<int>(TrackPiece::Tag::NUMBER_OF_TYPES)];
	InitTrackPieceTypes();

	active_control_point_[0] = true;
	active_control_point_[1] = false;
	active_control_point_[2] = true;
	active_control_point_[3] = false;

	update_mesh_ = false;

	track_preview_ = new TrackPreview(track->GetTrackMesh());

	preview_finished_ = false;
	//preview_track_piece_ = track_preview_->GetPreviewPiece();

}

//	Externally set is_active on each track piece.
bool* TrackBuilder::SetTrackPieceType(TrackPiece::Tag tag)
{
	return &track_piece_types_[static_cast<int>(tag)].is_active;
}

//	Update the track based on changes in settings.
void TrackBuilder::UpdateTrack()
{
	//	Determine if the user has added a new track piece.
	for (int i = 0; i < static_cast<int>(TrackPiece::Tag::NUMBER_OF_TYPES); i++)
	{
		if (track_piece_types_[i].is_active)
		{
			track_piece_types_[i].is_active = false;

			if (track_->GetTrackPieceCount() != 0)
			{
				track_->UpdateBack(track_piece_);
				track_->GenerateMesh();

			}
			update_mesh_ = true;

			track_->AddTrackPiece(track_piece_types_[i].tag);
			SetTrackPieceData();

			//	Pass the new track piece to the preview track for simulation.
			track_preview_->InitTrackPiece(track_->GetBack());
			track_piece_ = track_preview_->GetPreviewPiece();

			//	Pass starting conditions for simulation to the track preview. 
			track_preview_->InitialiseSimulation(track_->GetRollStore(), track_->GetForwardStore(), 
				track_->GetRightStore(), track_->GetUpStore(), track_->GetTargetRollStore());
		}
	}

	//	Update the track preview mesh.
	if (track_piece_)
	{
		if (track_piece_->GetRollTarget() != track_piece_data_.roll_target)
		{
			track_piece_->SetRollTarget(track_piece_data_.roll_target);
			update_mesh_ = true;
		}

		if (update_mesh_)
		{
			SL::Vector p0(track_piece_data_.p0_x, track_piece_data_.p0_y, track_piece_data_.p0_z);
			SL::Vector p1(track_piece_data_.p1_x, track_piece_data_.p1_y, track_piece_data_.p1_z);
			SL::Vector p2(track_piece_data_.p2_x, track_piece_data_.p2_y, track_piece_data_.p2_z);
			SL::Vector p3(track_piece_data_.p3_x, track_piece_data_.p3_y, track_piece_data_.p3_z);
			track_piece_->SetControlPoints(p0, p1, p2, p3);

			track_piece_->GetSpline()->CalculateCoefficients(track_piece_->GetTension());

			track_preview_->CalculateLength();
		}
	}

	if (preview_finished_)
	{
		track_->UpdateBack(track_piece_);
		track_->GenerateMesh();
		track_preview_->SetPreviewFinished(preview_finished_);
		preview_finished_ = false;
	}

	if (update_mesh_)
	{
		track_preview_->GenerateMesh();
		update_mesh_ = false;
	}
}

void TrackBuilder::SetTrackPieceData()
{
	TrackPiece* track_piece = track_->GetBack();

	if (track_piece)
	{
		SL::Vector p0 = track_piece->GetControlPoint(0);
		SL::Vector p1 = track_piece->GetControlPoint(1);
		SL::Vector p2 = track_piece->GetControlPoint(2);
		SL::Vector p3 = track_piece->GetControlPoint(3);

		track_piece_data_.p0_x = p0.X();
		track_piece_data_.p0_y = p0.Y();
		track_piece_data_.p0_z = p0.Z();

		track_piece_data_.p1_x = p1.X();
		track_piece_data_.p1_y = p1.Y();
		track_piece_data_.p1_z = p1.Z();

		track_piece_data_.p2_x = p2.X();
		track_piece_data_.p2_y = p2.Y();
		track_piece_data_.p2_z = p2.Z();

		track_piece_data_.p3_x = p3.X();
		track_piece_data_.p3_y = p3.Y();
		track_piece_data_.p3_z = p3.Z();

		track_piece_data_.roll_target = track_piece->GetRollTarget();
	}
}

void TrackBuilder::InitTrackPieceTypes()
{
	for (int i = 0; i < static_cast<int>(TrackPiece::Tag::NUMBER_OF_TYPES); i++)
	{
		track_piece_types_[i].tag = static_cast<TrackPiece::Tag>(i);
		track_piece_types_[i].is_active = false;
	}
}

TrackBuilder::~TrackBuilder()
{
	if (track_piece_types_)
	{
		delete[] track_piece_types_;
		track_piece_types_ = 0;
	}

	if (track_preview_)
	{
		delete track_preview_;
		track_preview_ = 0;
	}
}

int* TrackBuilder::SetRollTarget()
{
	return &track_piece_data_.roll_target;
}

bool TrackBuilder::GetActiveControlPoint(int control_point)
{
	return active_control_point_[control_point];
}

bool* TrackBuilder::SetActiveControlPoint(int control_point)
{
	return &active_control_point_[control_point];
}

bool* TrackBuilder::SetPreviewFinished()
{
	return &preview_finished_;
}

//bool* TrackBuilder::SetPreviewActive()
//{
//	return &preview_active_;
//}
//
//bool TrackBuilder::GetPreviewActive()
//{
//	return preview_active_;
//}

void TrackBuilder::UpdatePreviewMesh()
{
	track_preview_->GenerateMesh();
}

void TrackBuilder::SetControlPoint(int control_point, char element, float value)
{
	update_mesh_ = true;

	if (control_point == 0)
	{
		SetP0(element, value);
	}
	else if (control_point == 1)
	{
		SetP1(element, value);
	}
	else if (control_point == 2)
	{
		SetP2(element, value);
	} 
	else
	{
		SetP3(element, value);
	}
}

void TrackBuilder::SetControlPoint(int control_point, SL::Vector values)
{
	update_mesh_ = true;

	switch (control_point)
	{
	case 0: SetP0(values);
		break;
	case 1: SetP1(values);
		break;
	case 2: SetP2(values);
		break;
	case 3: SetP3(values);
		break;
	}
}

SL::Vector TrackBuilder::GetControlPoint(int control_point)
{
	SL::Vector result;

	switch (control_point)
	{
	case 0: result = GetP0();
		break;
	case 1: result = GetP1();
		break;
	case 2: result = GetP2();
		break;
	case 3: result = GetP3();
		break;
	}

	return result;
}

float TrackBuilder::GetControlPoint(int control_point, char element)
{
	if (control_point == 0)
	{
		return GetP0(element);
	}
	else if (control_point == 1)
	{
		return GetP1(element);
	}
	else if (control_point == 2)
	{
		return GetP2(element);
	}
	else
	{
		return GetP3(element);
	}
}

void TrackBuilder::SetP0(char element, float value)
{
	if (element == 'x')
	{
		track_piece_data_.p0_x = value;
	}
	else if (element == 'y')
	{
		track_piece_data_.p0_y = value;
	}
	else
	{
		track_piece_data_.p0_z = value;
	}
}

void TrackBuilder::SetP1(char element, float value)
{
	if (element == 'x')
	{
		track_piece_data_.p1_x = value;
	}
	else if (element == 'y')
	{
		track_piece_data_.p1_y = value;
	}
	else
	{
		track_piece_data_.p1_z = value;
	}
}

void TrackBuilder::SetP2(char element, float value)
{
	if (element == 'x')
	{
		track_piece_data_.p2_x = value;
	}
	else if (element == 'y')
	{
		track_piece_data_.p2_y = value;
	}
	else
	{
		track_piece_data_.p2_z = value;
	}
}

void TrackBuilder::SetP3(char element, float value)
{
	if (element == 'x')
	{
		track_piece_data_.p3_x = value;
	}
	else if (element == 'y')
	{
		track_piece_data_.p3_y = value;
	}
	else
	{
		track_piece_data_.p3_z = value;
	}
}

void TrackBuilder::SetP0(SL::Vector values)
{
	track_piece_data_.p0_x = values.X();
	track_piece_data_.p0_y = values.Y();
	track_piece_data_.p0_z = values.Z();
}

void TrackBuilder::SetP1(SL::Vector values)
{
	track_piece_data_.p1_x = values.X();
	track_piece_data_.p1_y = values.Y();
	track_piece_data_.p1_z = values.Z();
}

void TrackBuilder::SetP2(SL::Vector values)
{
	track_piece_data_.p2_x = values.X();
	track_piece_data_.p2_y = values.Y();
	track_piece_data_.p2_z = values.Z();
}

void TrackBuilder::SetP3(SL::Vector values)
{
	track_piece_data_.p3_x = values.X();
	track_piece_data_.p3_y = values.Y();
	track_piece_data_.p3_z = values.Z();
}

float TrackBuilder::GetP0(char element)
{
	if (element == 'x')
	{
		return track_piece_data_.p0_x;
	}
	else if (element == 'y')
	{
		return track_piece_data_.p0_y;
	}
	else
	{
		return track_piece_data_.p0_z;
	}
}

float TrackBuilder::GetP1(char element)
{
	if (element == 'x')
	{
		return track_piece_data_.p1_x;
	}
	else if (element == 'y')
	{
		return track_piece_data_.p1_y;
	}
	else
	{
		return track_piece_data_.p1_z;
	}
}

float TrackBuilder::GetP2(char element)
{
	if (element == 'x')
	{
		return track_piece_data_.p2_x;
	}
	else if (element == 'y')
	{
		return track_piece_data_.p2_y;
	}
	else
	{
		return track_piece_data_.p2_z;
	}
}

float TrackBuilder::GetP3(char element)
{
	if (element == 'x')
	{
		return track_piece_data_.p3_x;
	}
	else if (element == 'y')
	{
		return track_piece_data_.p3_y;
	}
	else
	{
		return track_piece_data_.p3_z;
	}
}

SL::Vector TrackBuilder::GetP0()
{
	return SL::Vector(track_piece_data_.p0_x, track_piece_data_.p0_y, track_piece_data_.p0_z);
}

SL::Vector TrackBuilder::GetP1()
{
	return SL::Vector(track_piece_data_.p1_x, track_piece_data_.p1_y, track_piece_data_.p1_z);
}

SL::Vector TrackBuilder::GetP2()
{
	return SL::Vector(track_piece_data_.p2_x, track_piece_data_.p2_y, track_piece_data_.p2_z);
}

SL::Vector TrackBuilder::GetP3()
{
	return SL::Vector(track_piece_data_.p3_x, track_piece_data_.p3_y, track_piece_data_.p3_z);
}
