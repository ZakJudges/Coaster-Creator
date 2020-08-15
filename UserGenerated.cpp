#include "UserGenerated.h"

//	User Generated Track Piece. 
//		Spacing/Curvature can be changed by the user on demand.
//			By default, is a straght line.
UserGenerated::UserGenerated()
{
	SL::CRSpline* spline_segment = new SL::CRSpline();
	SL::Vector p0, p1, p2, p3;

	p0.Set(0.0f, 0.0f, -10.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 10.0f);
	p3.Set(0.0f, 0.0f, 20.0f);

	spline_segment->SetControlPoints(p0, p1, p2, p3);
	spline_segment_.push_back(spline_segment);

	tension_ = 1.0f;
	roll_target_ = 0.0f;

}

bool UserGenerated::ShouldSmooth()
{
	return false;
}

void UserGenerated::SetControlPoint(int index, SL::Vector point)
{

}

TrackPiece::Tag UserGenerated::GetTag()
{
	return Tag::USER_GENERATED;
}

void UserGenerated::SetTension(float tension)
{
	tension_ = tension;
}

float UserGenerated::GetTension()
{
	return tension_;
}

void UserGenerated::SetRollTarget(float roll_target)
{
	roll_target_ = roll_target;
}

float UserGenerated::GetRollTarget()
{
	return roll_target_;
}

UserGenerated::~UserGenerated()
{

}
