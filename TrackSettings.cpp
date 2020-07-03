#include "TrackSettings.h"

TrackSettings::TrackSettings() : next_segment_(TrackPiece::Tag::STRAIGHT)
{

}

TrackPiece::Tag TrackSettings::NextSegmentType()
{
	return next_segment_;
}

void TrackSettings::SetNextSegment(TrackPiece::Tag tag)
{
	next_segment_ = tag;
}

TrackSettings::~TrackSettings()
{

}
