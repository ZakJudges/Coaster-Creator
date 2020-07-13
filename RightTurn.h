#pragma once

#include "TrackPiece.h"

class RightTurn : public TrackPiece
{
public:
	RightTurn();
	float GetRollTarget();
	Tag GetTag();
	~RightTurn();
};