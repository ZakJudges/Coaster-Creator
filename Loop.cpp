#include "Loop.h"

Loop::Loop()
{
	SL::Vector p0, p1, p2, p3;
	SL::CRSpline* spline_segment = new SL::CRSpline();

	p0.Set(0.0f, 0.0f, -10.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 10.0f);
	p3.Set(0.0f, 0.0f, 20.0f);
	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);

	spline_segment = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, 0.0f);
	p1.Set(0.0f, -5.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 5.0f);
	p3.Set(0.0f, 5.0f, 0.0f);
	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);

	spline_segment = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, 0.0f);
	p1.Set(0.0f, -5.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 5.0f);
	p3.Set(0.0f, 5.0f, 0.0f);
	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);

	spline_segment = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, 0.0f);
	p1.Set(1.0f, -5.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 5.0f);
	p3.Set(0.0f, 5.0f, 0.0f);
	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment->SetPreventYInversion(false);
	spline_segment_.push_back(spline_segment);

	spline_segment = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, 0.0f);
	p1.Set(1.0f, -5.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 5.0f);
	p3.Set(0.0f, 5.0f, 0.0f);
	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);

	spline_segment = new SL::CRSpline();
	p0.Set(0.0f, 0.0f, -10.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 10.0f);
	p3.Set(0.0f, 0.0f, 20.0f);
	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);
}

TrackPiece::Tag Loop::GetTag()
{
	return Tag::LOOP;
}

Loop::~Loop()
{

}
