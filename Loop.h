#pragma once

#include "TrackPiece.h"

class Loop : public TrackPiece
{
public:
	Loop();
	Tag GetTag();
	~Loop();
};