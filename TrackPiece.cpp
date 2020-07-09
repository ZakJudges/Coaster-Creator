#include "TrackPiece.h"

TrackPiece::TrackPiece() : spline_segment_(nullptr)
{

}

TrackPiece::Tag TrackPiece::GetTag()
{
	return Tag::NUMBER_OF_TYPES;
}

bool TrackPiece::ShouldSmooth()
{
	return true;
}

SL::CRSpline* TrackPiece::GetSpline()
{
	return spline_segment_;
}

TrackPiece::~TrackPiece()
{
	//	SplineController is responsible for memory management of spline segments.
	//		So only call delete if the spline controller does not use this segment.
	if (spline_segment_)
	{
		if (!spline_segment_->IsUsed())
		{
			delete spline_segment_;
			spline_segment_ = 0;
		}
	}
}
