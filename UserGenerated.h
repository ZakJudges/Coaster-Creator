#pragma once

#include "TrackPiece.h"

class UserGenerated : public TrackPiece
{
public:
	UserGenerated(TrackPiece* join_piece);
	void SetControlPoint(int index, SL::Vector point);
	bool ShouldSmooth();

	

	Tag GetTag();
	~UserGenerated();
};

