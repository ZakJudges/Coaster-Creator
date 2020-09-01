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
	void SetInitialRoll(float roll);
	float GetRollTarget();
	SL::Vector GetControlPoint(int element);
	void SetControlPoint(int control_point, SL::Vector);
	void SetControlPoints(SL::Vector p0, SL::Vector p1, SL::Vector p2, SL::Vector p3);

	void StoreOrientation(SL::Vector up, SL::Vector right, SL::Vector forward);
	SL::Vector GetInitUp();
	SL::Vector GetInitForward();
	SL::Vector GetInitRight();
	float GetInitRoll();

	int GetNumberOfSplines();

	SL::CRSpline* GetSpline(int index);
	void SetSplineSegment(SL::CRSpline* segment);
	void CalculateSpline();

	inline bool OrientationStored() { return orientation_stored_; }
protected:
	std::vector<SL::CRSpline*> spline_segment_;
	float length_;
	float tension_;
	float roll_target_;
	float roll_initial_;
	bool orientation_stored_;

	SL::Vector initial_up_;
	SL::Vector initial_forward_;
	SL::Vector initial_right_;

private:
};