#pragma once

#include "Track.h"

class TrackSettings
{
public:
	TrackSettings();
	TrackPiece::Tag NextSegmentType();
	void SetNextSegment(TrackPiece::Tag tag);
	~TrackSettings();
private:
	TrackPiece::Tag next_segment_;
};
