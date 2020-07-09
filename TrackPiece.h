#pragma once

#include "../Splines/CRSpline.h"



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
		COMPLETE_TRACK,
		UNDO,
		NUMBER_OF_TYPES
	};

	TrackPiece();
	virtual ~TrackPiece();

	virtual Tag GetTag();
	virtual bool ShouldSmooth();

	SL::CRSpline* GetSpline();

protected:
	SL::CRSpline* spline_segment_;

private:
};