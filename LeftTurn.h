#pragma once

#include "TrackPiece.h"

class LeftTurn : public TrackPiece
{
public:
	LeftTurn();
	float GetRollTarget();
	Tag GetTag();
	~LeftTurn();
};