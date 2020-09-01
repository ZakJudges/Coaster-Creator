#pragma once

#include "Track.h"

class TrackPreview;

class TrackBuilder
{
public:
	struct TrackPieceType
	{
		TrackPiece::Tag tag;
		bool is_active;
	};
	struct TrackPieceData
	{
		float p0_x, p0_y, p0_z;
		float p1_x, p1_y, p1_z;
		float p2_x, p2_y, p2_z;
		float p3_x, p3_y, p3_z;
		int roll_target;
	};
	TrackBuilder(Track* track);
	bool UpdateTrack();
	bool* SetTrackPieceType(TrackPiece::Tag tag);
	
	bool GetActiveControlPoint(int control_point);
	bool* SetActiveControlPoint(int control_point);


	int* SetRollTarget();
	void SetControlPoint(int control_point, char element, float value);
	float GetControlPoint(int control_point, char element);
	void SetP0(char element, float value);
	void SetP1(char element, float value);
	void SetP2(char element, float value);
	void SetP3(char element, float value);

	float GetP0(char element);
	float GetP1(char element);
	float GetP2(char element);
	float GetP3(char element);


	~TrackBuilder();

private:
	void InitTrackPieceTypes();
	void SetTrackPieceData();
private:
	Track* track_;
	TrackPreview* track_preview_;
	TrackPieceType* track_piece_types_;
	TrackPieceData track_piece_data_;
	TrackPiece* track_piece_;
	TrackPiece* preview_track_piece_;
	bool active_control_point_[4];
	bool update_mesh_;
};
