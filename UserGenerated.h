#pragma once

#include "TrackPiece.h"

class UserGenerated : public TrackPiece
{
public:
	UserGenerated();
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

	//	Get/SetTension();
	//	Get/Set Roll Target();
};