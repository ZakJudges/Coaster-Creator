#pragma once

#include "../Spline-Library/CRSpline.h"

#include <vector>



class TrackPiece
{
public:
	enum class Tag
	{
		STRAIGHT = 0,
		RIGHT_TURN,
		LEFT_TURN,
		CLIMB_UP,
		CLIMB_DOWN,
		LOOP,
		COMPLETE_TRACK,
		UNDO,
		USER_GENERATED,
		NUMBER_OF_TYPES
	};

	struct Boundary
	{
		float t0;
		float t1;
	};
	Boundary bounding_values_;


	TrackPiece();
	void SetLength(float length);
	inline float GetLength() { return length_; }
	virtual ~TrackPiece();

	virtual Tag GetTag();
	virtual bool ShouldSmooth();		
	
	void SetTension(float tension);
	float GetTension();
	void SetRollTarget(float roll_target);
	float GetRollTarget();
	SL::Vector GetControlPoint(int element);
	void SetControlPoint(int control_point, SL::Vector);
	void SetControlPoints(SL::Vector p0, SL::Vector p1, SL::Vector p2, SL::Vector p3);

	int GetNumberOfSplines();

	SL::CRSpline* GetSpline(int index);

protected:
	std::vector<SL::CRSpline*> spline_segment_;
	float length_;
	float tension_;
	float roll_target_;

private:
};