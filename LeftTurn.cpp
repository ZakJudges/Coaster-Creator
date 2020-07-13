#include "LeftTurn.h"

LeftTurn::LeftTurn()
{
	SL::CRSpline* spline_segment = new SL::CRSpline();
	SL::Vector p0, p1, p2, p3;

	p0.Set(-10.0f, 0.0f, 0.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(-10.0f, 0.0f, 10.0f);
	p3.Set(-10.0f, 0.0f, 0.0f);

	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);
}

float LeftTurn::GetRollTarget()
{
	return 45.0f;
}

TrackPiece::Tag LeftTurn::GetTag()
{
	return Tag::LEFT_TURN;
}

LeftTurn::~LeftTurn()
{

}