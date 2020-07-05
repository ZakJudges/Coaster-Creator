#include "LeftTurn.h"

LeftTurn::LeftTurn()
{
	spline_segment_ = new SL::CRSpline();
	SL::Vector p0, p1, p2, p3;

	p0.Set(-10.0f, 0.0f, 0.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(-10.0f, 0.0f, 10.0f);
	p3.Set(-10.0f, 0.0f, 0.0f);

	spline_segment_->SetControlPoints(p0, p1, p2, p3);
}

TrackPiece::Tag LeftTurn::GetTag()
{
	return Tag::LEFT_TURN;
}

LeftTurn::~LeftTurn()
{
	if (spline_segment_)
	{
		delete spline_segment_;
		spline_segment_ = 0;
	}
}