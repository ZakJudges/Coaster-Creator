#pragma once

#include "TrackPiece.h"

#include <vector>
//#include "../DXFramework/BaseMesh.h"
//#include "../Splines/CRSplineController.h"
#include "../Spline-Library/CRSplineController.h"
#include <directxmath.h>

class SplineMesh;
class PipeMesh;

class Track
{
public:
	Track(const int resolution, SplineMesh* spline_mesh, PipeMesh* pipe_mesh);
	void AddTrackPiece(TrackPiece::Tag tag);
	void Update(float t);
	void GenerateMesh();
	DirectX::XMFLOAT3 GetPoint();
	DirectX::XMFLOAT3 GetPointAtDistance(float d);
	DirectX::XMFLOAT3 GetPointAtTime(float t);
	DirectX::XMFLOAT3 GetForward();
	DirectX::XMFLOAT3 GetUp();
	DirectX::XMFLOAT3 GetRight();
	~Track();

private:
	void RemoveBack();
	bool CreateTrackPiece(TrackPiece* track_piece);
	void CalculatePieceBoundaries();
	void StoreMeshData(TrackPiece* track_piece);
	int GetActiveTrackPiece();
	float Lerpf(float f0, float f1, float t);

private:
	std::vector<TrackPiece*> track_pieces_;
	SL::CRSplineController* spline_controller_;
	SplineMesh* spline_mesh_;
	PipeMesh* pipe_mesh_;
	int resolution_;
	float t_;

	SL::Vector forward_;
	SL::Vector right_;
	SL::Vector up_;
	float roll_;
	
};