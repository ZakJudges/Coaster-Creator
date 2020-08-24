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
	struct TrackPieceData
	{
		SL::Vector p0;
		SL::Vector p1;
		SL::Vector p2;
		SL::Vector p3;
		int roll_target;
	};
	TrackBuilder(Track* track);
	bool UpdateTrack();
	bool* SetTrackPieceType(TrackPiece::Tag tag);
	int* SetRollTarget();
	~TrackBuilder();
private:
	void InitTrackPieceTypes();
	void SetTrackPieceData();
private:
	Track* track_;
	TrackPieceType* track_piece_types_;
	TrackPieceData track_piece_data_;
	TrackPiece* track_piece_;
};
