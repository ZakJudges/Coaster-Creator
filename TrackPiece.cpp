#include "TrackPiece.h"

TrackPiece::TrackPiece()
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

SL::CRSpline* TrackPiece::GetSpline(int index)
{
	return spline_segment_[index];
}

int TrackPiece::GetNumberOfSplines()
{
	return spline_segment_.size();
}

TrackPiece::~TrackPiece()
{
	//	SplineController is responsible for memory management of spline segments.
	//		So only call delete if the spline controller does not use this segment.
	for (int i = 0; i < spline_segment_.size(); i++)
	{
		if (spline_segment_[i])
		{
			if (!spline_segment_[i]->IsUsed())
			{
				delete spline_segment_[i];
				spline_segment_[i] = 0;
			}
		}
	}
	
}
