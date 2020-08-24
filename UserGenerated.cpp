#include "UserGenerated.h"

//	User Generated Track Piece. 
//		Spacing/Curvature can be changed by the user on demand.
UserGenerated::UserGenerated(TrackPiece* join_piece)
{
	//SL::Vector join_point, SL::Vector tangent_in

	//	Determine the initial values for the spline segment.
	SL::CRSpline* spline_segment = new SL::CRSpline();
	SL::Vector p0, p1, p2, p3;

	p0.Set(0.0f, 0.0f, -10.0f);
	p1.Set(0.0f, 0.0f, 0.0f);
	p2.Set(0.0f, 0.0f, 10.0f);
	p3.Set(0.0f, 0.0f, 20.0f);

	if (join_piece)
	{
		SL::CRSpline* join_to = join_piece->GetSpline(0);

		//	Calculate the difference in position.
		SL::Vector pos_diff = join_to->GetControlPoint(2).Subtract(p1);

		//p0 = p0.Add(pos_diff);
		p1 = p1.Add(pos_diff);
		p2 = p2.Add(pos_diff);
		p3 = p3.Add(pos_diff);

		p0 = p2.Add(join_to->GetControlPoint(1)).Subtract(join_to->GetControlPoint(3));
	}
	
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
	//TEMP. Only alter one spline segment control point.
	spline_segment_[0]->SetControlPoint(point, index);



	//	TODO: This is inefficient. Add a function that recalculated the coefficients when the user has finished moving the point.
	for (int i = 0; i < spline_segment_.size(); i++)
	{
		spline_segment_[i]->CalculateCoefficients(tension_);
	}
}

TrackPiece::Tag UserGenerated::GetTag()
{
	return Tag::USER_GENERATED;
}

UserGenerated::~UserGenerated()
{

}
