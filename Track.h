#pragma once

#include "TrackPiece.h"

#include <vector>
//#include "../DXFramework/BaseMesh.h"
#include "../Splines/CRSplineController.h"

#include <directxmath.h>

class SplineMesh;

class Track
{
public:
	Track(const int resolution, SplineMesh* spline_mesh);
	void AddTrackPiece(TrackPiece::Tag tag);
	void Update(float t);
	DirectX::XMFLOAT3 GetPoint();
	DirectX::XMFLOAT3 GetPointAtDistance(float d);
	DirectX::XMFLOAT3 GetForward();//TEMP.
	DirectX::XMFLOAT3 GetUp();//TEMP.
	DirectX::XMFLOAT3 GetRight();//TEMP.
	~Track();

private:
	void RemoveBack();
	bool CreateTrackPiece(TrackPiece* track_piece);
	void CalculatePieceBoundaries();
	int GetActiveTrackPiece();
	float Lerpf(float f0, float f1, float t);

private:
	std::vector<TrackPiece*> track_pieces_;
	SL::CRSplineController* spline_controller_;
	SplineMesh* spline_mesh_;
	int resolution_;
	float t_;

	SL::Vector forward_;
	SL::Vector right_;
	SL::Vector up_;
	float roll_;
};