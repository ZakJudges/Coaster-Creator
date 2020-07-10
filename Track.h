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
	DirectX::XMVECTOR GetPointAtTime(const float t);//TEMP.
	DirectX::XMFLOAT3 GetForward(const float t);//TEMP.
	DirectX::XMFLOAT3 GetUp(const float t);//TEMP.
	DirectX::XMFLOAT3 GetRight(const float t);//TEMP.
	~Track();

private:
	void RemoveBack();

private:
	std::vector<TrackPiece*> track_pieces_;
	SL::CRSplineController* spline_controller_;
	SplineMesh* spline_mesh_;
	int resolution_;
};