#include "TrackBuilder.h"

TrackBuilder::TrackBuilder(Track* track) : track_(track)
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
void TrackBuilder::UpdateTrack()
{
	for (int i = 0; i < static_cast<int>(TrackPiece::Tag::NUMBER_OF_TYPES); i++)
	{
		if (track_piece_types_[i].is_active)
		{
			track_piece_types_[i].is_active = false;
			track_->AddTrackPiece(track_piece_types_[i].tag);
			break;
		}
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
}
