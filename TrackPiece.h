#pragma once

#include "../Splines/CRSpline.h"



class TrackPiece
{
public:
	enum class Tag
	{
		NO_TAG = 0,
		STRAIGHT,
		RIGHT_TURN,
		LEFT_TURN
	};

	TrackPiece();
	virtual ~TrackPiece();

	virtual Tag GetTag();

	SL::CRSpline* GetSpline();

protected:
	SL::CRSpline* spline_segment_;

private:
};