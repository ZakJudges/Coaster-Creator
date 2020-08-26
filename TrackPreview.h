#pragma once

#include <vector>
#include "../Spline-Library/vector.h"

class TrackPiece;
class TrackMesh;

namespace SL
{
	class CRSplineController;
}

class TrackPreview
{
public:
	TrackPreview(TrackMesh* track_mesh);
	void InitTrackPiece(TrackPiece* track_piece);
	void UpdateSimulation(float t);
	TrackPiece* GetPreviewPiece();
	void GenerateMesh();
	~TrackPreview();

private:
	TrackPiece* track_piece_;
	SL::CRSplineController* spline_controller_;
	TrackMesh* track_mesh_;

	float t_;

	SL::Vector initial_forward_;
	SL::Vector forward_;

	SL::Vector right_;
	SL::Vector initial_right_;

	SL::Vector up_;
	SL::Vector initial_up_;
};