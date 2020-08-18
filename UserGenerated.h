#pragma once

#include "TrackPiece.h"

class UserGenerated : public TrackPiece
{
public:
	UserGenerated(TrackPiece* join_piece);
	void SetControlPoint(int index, SL::Vector point);
	bool ShouldSmooth();

	void SetTension(float tension);
	float GetTension();
	void SetRollTarget(float roll_target);
	float GetRollTarget();

	Tag GetTag();
	~UserGenerated();
private:
	float tension_;
	float roll_target_;
};

