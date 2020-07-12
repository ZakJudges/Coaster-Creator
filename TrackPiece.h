#pragma once

#include "../Splines/CRSpline.h"

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

	TrackPiece();
	virtual ~TrackPiece();

	virtual Tag GetTag();
	virtual bool ShouldSmooth();
	virtual float GetTension();

	int GetNumberOfSplines();

	SL::CRSpline* GetSpline(int index);

protected:
	std::vector<SL::CRSpline*> spline_segment_;

private:
};