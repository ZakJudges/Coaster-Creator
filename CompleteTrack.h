#pragma once

#include "TrackPiece.h"

//	Track piece with customisable control points.
//		Used for the final spline segment.
class CompleteTrack : public TrackPiece
{
public:
	CompleteTrack(SL::CRSpline* segment);
	Tag GetTag();
	bool ShouldSmooth();
	~CompleteTrack();
};