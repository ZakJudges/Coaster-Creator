#include "CompleteTrack.h"

CompleteTrack::CompleteTrack(SL::CRSpline* segment)
{
	spline_segment_ = segment;
}

TrackPiece::Tag CompleteTrack::GetTag()
{
	return Tag::COMPLETE_TRACK;
}

bool CompleteTrack::ShouldSmooth()
{
	return false;
}

CompleteTrack::~CompleteTrack()
{

}
