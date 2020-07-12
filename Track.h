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
	bool AddTrackPiece(TrackPiece::Tag tag);
	void SetTime(float t);
	DirectX::XMFLOAT3 GetPoint();
	DirectX::XMFLOAT3 GetPointAtDistance(float d);
	DirectX::XMFLOAT3 GetForward();//TEMP.
	DirectX::XMFLOAT3 GetUp();//TEMP.
	DirectX::XMFLOAT3 GetRight();//TEMP.
	~Track();

private:
	void RemoveBack();

private:
	std::vector<TrackPiece*> track_pieces_;
	SL::CRSplineController* spline_controller_;
	SplineMesh* spline_mesh_;
	int resolution_;
	float t_;

	SL::Vector forward_;
	SL::Vector right_;
	SL::Vector up_;
};