#pragma once

#include "TrackPiece.h"
#include <vector>
#include <directxmath.h>

//	Forward declarations.
class SplineMesh;
class TrackMesh;

namespace SL
{
	class CRSplineController;
}

//	The track is modified by the track builder when the application is in the building state.
//		This class generates orientation vectors at points along the spline, which are used to generate the mesh.
//
//	The track is stepped through when the application is in the simulating state.
//		This class generates different orientation vectors along the spline, for the coaster camera.
class Track
{
public:
	Track(const int resolution, TrackMesh* track_mesh);
	~Track();

	//	Building.
	void AddTrackPiece(TrackPiece::Tag tag);
	void AddTrackPieceFromFile(TrackPiece* track_piece);
	void LoadTrack();
	void CalculatePieceBoundaries();
	void StoreMeshData();
	void GenerateMesh();
	void GenerateSupportStructures();
	void EraseTrack();
	float GetTrackLength();
	float RecalculateTrackLength();
	int GetTrackPieceCount();
	void UpdateBack(TrackPiece* track_piece);
	void RemoveBack();
	inline unsigned int GetMaxTrackPieceCount() { return max_segments_; }
	TrackMesh* GetTrackMesh();

	//	Simulating.
	void Reset();
	void CalculateEndOfSimulation();
	TrackPiece* GetBack();
	TrackPiece* GetTrackPiece(int index);
	DirectX::XMVECTOR GetCameraEye();
	DirectX::XMVECTOR GetCameraLookAt();
	DirectX::XMVECTOR GetCameraUp();
	DirectX::XMFLOAT3 GetPoint();
	DirectX::XMFLOAT3 GetPointAtDistance(float d);
	DirectX::XMFLOAT3 GetPointAtTime(float t);
	DirectX::XMFLOAT3 GetForward();
	DirectX::XMFLOAT3 GetUp();
	DirectX::XMFLOAT3 GetRight();
	SL::Vector GetTangent();
	SL::Vector GetForwardStore();
	SL::Vector GetUpStore();
	SL::Vector GetRightStore();
	inline float GetTargetRollStore() { return target_roll_store_; }
	inline float GetRollStore() { return roll_store_; }
	void UpdateSimulation(float t);

private:
	void StoreSimulationValues();
	std::vector<SL::Vector> GetBoundingSphereCentres(int sphere_count);
	int GetActiveTrackPiece();
	float Lerpf(float f0, float f1, float t);

private:
	unsigned int max_segments_;
	std::vector<TrackPiece*> track_pieces_;
	SL::CRSplineController* spline_controller_;
	TrackMesh* track_mesh_;
	int resolution_;
	float t_;
	SL::Vector initial_forward_;
	SL::Vector forward_;
	SL::Vector right_;
	SL::Vector initial_right_;
	SL::Vector up_;
	SL::Vector initial_up_;
	float roll_;	
	float roll_store_;
	float target_roll_store_;
	SL::Vector forward_store_;
	SL::Vector right_store_;
	SL::Vector up_store_;
	bool preview_active_;
	float min_height_;
};