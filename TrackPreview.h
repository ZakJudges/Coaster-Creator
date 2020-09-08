#pragma once

#include <vector>
#include "../Spline-Library/vector.h"
#include <directxmath.h>


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
	void InitialiseRoll(float roll);
	inline float GetRoll() { return roll_; }
	void InitTrackPiece(TrackPiece* track_piece);
	void UpdateSimulation(float t);
	TrackPiece* GetPreviewPiece();
	void GenerateMesh();
	void InitialiseForward(SL::Vector forward);
	void InitialiseRight(SL::Vector right);
	void InitialiseUp(SL::Vector up);
	void SetPreviousRollTarget(float roll);
	void CalculateLength();
	~TrackPreview();
private:
	float Lerpf(float f0, float f1, float t);
	void Reset();
	DirectX::XMFLOAT3 GetPointAtDistance(float d);
	DirectX::XMFLOAT3 GetForward();
	DirectX::XMFLOAT3 GetUp();
	DirectX::XMFLOAT3 GetRight();

private:
	TrackPiece* track_piece_;
	SL::CRSplineController* spline_controller_;
	TrackMesh* track_mesh_;

	float t_;

	float initial_roll_;
	float roll_;
	
	SL::Vector initial_forward_;
	SL::Vector forward_;

	SL::Vector right_;
	SL::Vector initial_right_;

	SL::Vector up_;
	SL::Vector initial_up_;
};