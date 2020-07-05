#pragma once

#include "Track.h"

class TrackBuilder
{
public:
	struct TrackPieceType
	{
		TrackPiece::Tag tag;
		bool is_active;
	};
	TrackBuilder(Track* track);
	void UpdateTrack();
	bool* SetTrackPieceType(TrackPiece::Tag tag);
	~TrackBuilder();
private:
	void InitTrackPieceTypes();
private:
	Track* track_;
	TrackPieceType* track_piece_types_;
};
