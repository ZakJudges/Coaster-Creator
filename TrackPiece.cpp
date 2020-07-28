#include "TrackPiece.h"

TrackPiece::TrackPiece()
{
	bounding_values_.t0 = 0.0f;
	bounding_values_.t1 = 1.0f;
	length_ = 0.0f;
}

void TrackPiece::SetLength(float length)
{
	length_ = length;
}

TrackPiece::Tag TrackPiece::GetTag()
{
	return Tag::NUMBER_OF_TYPES;
}

bool TrackPiece::ShouldSmooth()
{
	return true;
}

float TrackPiece::GetTension()
{
	return 1.0f;
}

float TrackPiece::GetRollTarget()
{
	return 0.0f;
}

SL::CRSpline* TrackPiece::GetSpline(int index)
{
	return spline_segment_[index];
}

int TrackPiece::GetNumberOfSplines()
{
	return spline_segment_.size();
}

unsigned int TrackPiece::GetMeshResolution()
{
	return 20;
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
