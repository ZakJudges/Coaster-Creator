#include "TrackBuilder.h"

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
}

//	Externally set is_active on each track piece.
bool* TrackBuilder::SetTrackPieceType(TrackPiece::Tag tag)
{
	return &track_piece_types_[static_cast<int>(tag)].is_active;
}

//	Update the track based on changes in settings.
bool TrackBuilder::UpdateTrack()
{
	

	//	Determine if the user has added a new track piece.
	for (int i = 0; i < static_cast<int>(TrackPiece::Tag::NUMBER_OF_TYPES); i++)
	{
		if (track_piece_types_[i].is_active)
		{
			track_piece_types_[i].is_active = false;
			track_->AddTrackPiece(track_piece_types_[i].tag);
			SetTrackPieceData();
		}
	}


	//	TODO: call only when a change to the track piece data has been detected.
	if (track_piece_)
	{
		if (track_piece_->GetRollTarget() != track_piece_data_.roll_target)
		{
			track_piece_->SetRollTarget(track_piece_data_.roll_target);
			update_mesh_ = true;
		}

		if (update_mesh_)
		{
			//	Store the length of the track prior to updating the control points,
			//		so we can calculate the length of the altered track piece. 
			float old_length = track_->GetTrackLength();

			SL::Vector p0(track_piece_data_.p0_x, track_piece_data_.p0_y, track_piece_data_.p0_z);
			SL::Vector p1(track_piece_data_.p1_x, track_piece_data_.p1_y, track_piece_data_.p1_z);
			SL::Vector p2(track_piece_data_.p2_x, track_piece_data_.p2_y, track_piece_data_.p2_z);
			SL::Vector p3(track_piece_data_.p3_x, track_piece_data_.p3_y, track_piece_data_.p3_z);
			track_piece_->SetControlPoints(p0, p1, p2, p3);

			track_piece_->GetSpline(0)->CalculateCoefficients(track_piece_->GetTension());

			//	Calculate the length of the new track piece.
			float new_length = track_->RecalculateTrackLength();

			float length_diff = new_length - old_length;
			track_piece_->SetLength(track_piece_->GetLength() + length_diff);
			track_->CalculatePieceBoundaries();

			update_mesh_ = false;
			return true;
		}
	}

	return false;
}

void TrackBuilder::SetTrackPieceData()
{
	track_piece_ = track_->GetBack();

	SL::Vector p0 = track_piece_->GetControlPoint(0);
	SL::Vector p1 = track_piece_->GetControlPoint(1);
	SL::Vector p2 = track_piece_->GetControlPoint(2);
	SL::Vector p3 = track_piece_->GetControlPoint(3);

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

	track_piece_data_.roll_target = track_piece_->GetRollTarget();
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
