#include "TrackPiece.h"

TrackPiece::TrackPiece()
{
	bounding_values_.t0 = 0.0f;
	bounding_values_.t1 = 1.0f;
	length_ = 0.0f;
	roll_target_ = 0.0f;
	roll_initial_ = 0.0f;
	tension_ = 1.0f;
	orientation_stored_ = false;
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
	return tension_;
}

void TrackPiece::SetTension(float tension)
{
	tension_ = tension;
}

void TrackPiece::SetRollTarget(float roll_target)
{
	roll_target_ = roll_target;
}

float TrackPiece::GetRollTarget()
{
	//return 0.0f;
	return roll_target_;
}

SL::Vector TrackPiece::GetControlPoint(int element)
{
	return spline_segment_[0]->GetControlPoint(element);
}

void TrackPiece::SetControlPoint(int control_point, SL::Vector point)
{
	spline_segment_[0]->SetControlPoint(point, control_point);
}

void TrackPiece::SetControlPoints(SL::Vector p0, SL::Vector p1, SL::Vector p2, SL::Vector p3)
{
	spline_segment_[0]->SetControlPoints(p0, p1, p2, p3);
}

SL::CRSpline* TrackPiece::GetSpline(int index)
{
	return spline_segment_[index];
}

int TrackPiece::GetNumberOfSplines()
{
	return spline_segment_.size();
}

void TrackPiece::CalculateSpline()
{
	spline_segment_[0]->CalculateCoefficients(GetTension());
}

void TrackPiece::SetSplineSegment(SL::CRSpline* segment)
{
	spline_segment_.push_back(segment);
}

void TrackPiece::StoreOrientation(SL::Vector up, SL::Vector right, SL::Vector forward)
{
	initial_up_ = up;
	initial_right_ = right;
	initial_forward_ = forward;
	orientation_stored_ = true;
}

SL::Vector TrackPiece::GetInitUp()
{
	return initial_up_;
}

SL::Vector TrackPiece::GetInitForward()
{
	return initial_forward_;
}

SL::Vector TrackPiece::GetInitRight()
{
	return initial_right_;
}

float TrackPiece::GetInitRoll()
{
	return roll_initial_;
}

void TrackPiece::SetInitialRoll(float roll)
{
	roll_initial_ = roll;
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
