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
	virtual float GetTension();
	virtual float GetRollTarget();
	virtual unsigned int GetMeshResolution();

	int GetNumberOfSplines();

	SL::CRSpline* GetSpline(int index);

protected:
	std::vector<SL::CRSpline*> spline_segment_;
	float length_;

private:
};