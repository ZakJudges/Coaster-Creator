#pragma once

#include "TrackPiece.h"

#include <vector>
//#include "../DXFramework/BaseMesh.h"
#include "../Splines/CRSplineController.h"

class SplineMesh;

class Track
{
public:
	Track(const int resolution, SplineMesh* spline_mesh);
	void AddTrackPiece(TrackPiece::Tag tag);
	~Track();

private:
	std::vector<TrackPiece*> track_pieces_;
	SL::CRSplineController* spline_controller_;
	SplineMesh* spline_mesh_;
	int resolution_;
};