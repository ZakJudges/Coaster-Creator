#include "Straight.h"

Straight::Straight()
{
	SL::CRSpline* spline_segment = new SL::CRSpline();
	SL::Vector p0, p1, p2, p3;

	p0.Set(0.0f, 0.0f, -10.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 10.0f);
	p3.Set(0.0f, 0.0f, 20.0f);

	spline_segment->SetControlPoints(p0, p1, p2, p3);

	spline_segment_.push_back(spline_segment);
}

unsigned int Straight::GetMeshResolution()
{
	return 5;
}

TrackPiece::Tag Straight::GetTag()
{
	return Tag::STRAIGHT;
}

Straight::~Straight()
{
	
}
