#pragma once

#include "Track.h"
#include "EditMode.h"

class TrackPreview;

class TrackBuilder
{
public:
	struct TrackPieceType
	{
		TrackPiece::Tag tag;
		bool is_active;
	};
	struct EditModeType
	{
		EditMode::EditModeTag tag;
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
	void UpdateTrack();
	void UpdatePreviewMesh();

	bool* SetTrackPieceType(TrackPiece::Tag tag);
	bool* SetEditModeTypeImGui(EditMode::EditModeTag tag);
	void SetEditModeType(EditMode::EditModeTag tag);
	bool GetActiveControlPoint(int control_point);
	bool* SetActiveControlPoint(int control_point);

	//bool* SetPreviewActive();
	bool* SetPreviewFinished();
	bool GetPreviewActive();


	bool* SetUndo();
	int* SetRollTarget();

	void SetControlPoint(int control_point, char element, float value);
	void SetControlPoint(int control_point, SL::Vector values);
	float GetControlPoint(int control_point, char element);
	SL::Vector GetControlPoint(int control_point);
	void SetP0(char element, float value);
	void SetP1(char element, float value);
	void SetP2(char element, float value);
	void SetP3(char element, float value);
	void SetP0(SL::Vector values);
	void SetP1(SL::Vector values);
	void SetP2(SL::Vector values);
	void SetP3(SL::Vector values);
	float GetP0(char element);
	float GetP1(char element);
	float GetP2(char element);
	float GetP3(char element);
	SL::Vector GetP0();
	SL::Vector GetP1();
	SL::Vector GetP2();
	SL::Vector GetP3();

	~TrackBuilder();

private:
	void InitTrackPieceTypes();
	void InitEditModeTypes();
	void SetTrackPieceData();
	void Build();
	void Undo();
	//TrackPiece* AddTrackPiece(TrackPiece::Tag tag);
private:
	Track* track_;
	TrackPreview* track_preview_;
	TrackPieceType* track_piece_types_;
	TrackPieceData track_piece_data_;
	TrackPiece* track_piece_;
	bool active_control_point_[4];

	EditMode* edit_mode_;
	EditModeType edit_mode_types_[4];
	EditModeMove move_;
	EditModeSoftCurve soft_curve_;
	EditModeHardCurve hard_curve_;
	EditModeFixedEnds fixed_ends_;
	void SetEditMode(EditMode::EditModeTag tag);

	bool update_preview_mesh_;
	bool preview_finished_;
	bool undo_;
};
