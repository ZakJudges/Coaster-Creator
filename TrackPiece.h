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
		NUMBER_OF_TYPES
	};

	TrackPiece();
	virtual ~TrackPiece();

	virtual Tag GetTag();

	SL::CRSpline* GetSpline();

protected:
	SL::CRSpline* spline_segment_;

private:
};