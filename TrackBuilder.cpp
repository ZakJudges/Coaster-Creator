#include "TrackBuilder.h"

TrackBuilder::TrackBuilder(Track* track) : track_(track), track_piece_(nullptr)
{
	//	Size based on total number of different track piece types.
	track_piece_types_ = new TrackPieceType[static_cast<int>(TrackPiece::Tag::NUMBER_OF_TYPES)];
	InitTrackPieceTypes();
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
			return true;
		}
	}

	//	TODO: call only when a change to the track piece data has been detected.
	if (track_piece_)
	{
		track_piece_->SetRollTarget(track_piece_data_.roll_target);
	}
	return false;
}

void TrackBuilder::SetTrackPieceData()
{
	track_piece_ = track_->GetBack();

	track_piece_data_.p0 = track_piece_->GetControlPoint(0);
	track_piece_data_.p1 = track_piece_->GetControlPoint(1);
	track_piece_data_.p2 = track_piece_->GetControlPoint(2);
	track_piece_data_.p3 = track_piece_->GetControlPoint(3);
	track_piece_data_.roll_target = track_piece_->GetRollTarget();
}

int* TrackBuilder::SetRollTarget()
{
	return &track_piece_data_.roll_target;
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
