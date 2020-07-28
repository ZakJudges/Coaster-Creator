#pragma once

#include "TrackPiece.h"

class Straight : public TrackPiece
{
public:
	Straight();
	unsigned int GetMeshResolution();
	Tag GetTag();
	~Straight();
};