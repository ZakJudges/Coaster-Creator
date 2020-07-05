#include "TrackPiece.h"

TrackPiece::TrackPiece() : spline_segment_(nullptr)
{

}

TrackPiece::Tag TrackPiece::GetTag()
{
	return Tag::NUMBER_OF_TYPES;
}

SL::CRSpline* TrackPiece::GetSpline()
{
	return spline_segment_;
}

TrackPiece::~TrackPiece()
{
	if (spline_segment_)
	{
		delete spline_segment_;
		spline_segment_ = 0;
	}
}
