#include "Track.h"

#include "SplineMesh.h"
#include "RightTurn.h"
#include "Straight.h"
#include "LeftTurn.h"
#include "ClimbUp.h"
#include "ClimbDown.h"
#include "CompleteTrack.h"
#include "Loop.h"
#include "../Spline-Library/matrix3x3.h"

Track::Track(const int resolution, SplineMesh* spline_mesh) : resolution_(resolution), spline_mesh_(spline_mesh), t_(0.0f)
{
	spline_controller_ = new SL::CRSplineController(resolution);

	//	To Do: Move to cart class.
	up_.Set(0.0f, 1.0f, 0.0f);
	right_.Set(1.0f, 0.0f, 0.0f);
	forward_.Set(0.0f, 0.0f, 1.0f);
	roll_ = 0.0f;
}

void Track::RemoveBack()
{
	if (track_pieces_.empty())
	{
		return;
	}

	TrackPiece* piece_to_remove = track_pieces_.back();
	if (piece_to_remove)
	{
		//	One track piece can have multiple spline segments, so remove the correct number of spline segments from the spline controller.
		for (int i = 0; i < piece_to_remove->GetNumberOfSplines(); i++)
		{
			spline_controller_->RemoveBack();
		}

		track_pieces_.pop_back();
		delete piece_to_remove;
		piece_to_remove = 0;
	}

	//	Update the spline mesh, so that the removed track piece is not displayed.
	if (spline_mesh_)
	{
		spline_mesh_->Update(spline_controller_);
	}
}

bool Track::CreateTrackPiece(TrackPiece* track_piece)
{
	if (track_piece)
	{
		int counter = 0;
		float previous_length = spline_controller_->GetArcLength();

		for (int i = 0; i < track_piece->GetNumberOfSplines(); i++)
		{
			if (spline_controller_->AddSegment(track_piece->GetSpline(i), track_piece->GetTension(), track_piece->ShouldSmooth()))
			{
				//	Spline segment successfully added to the spline controller.
				counter++;
			}
		}

		if (counter != track_piece->GetNumberOfSplines())
		{
			//	Not all segments making up this track piece could be added to the spline.
			//		Deallocate the segments that were added, as well as the track piece.
			for (int j = 0; j < counter; j++)
			{
				spline_controller_->RemoveBack();
			}
			delete track_piece;
			track_piece = 0;

			return false;
		}

		track_piece->SetLength(spline_controller_->GetArcLength() - previous_length);

		track_pieces_.push_back(track_piece);

		if (spline_mesh_)
		{
			spline_mesh_->Update(spline_controller_);
		}
	}
	else
	{
		return false;
	}

	return true;
}

void Track::AddTrackPiece(TrackPiece::Tag tag)
{
	TrackPiece* track_piece = nullptr;

	switch (tag)
	{
	case TrackPiece::Tag::STRAIGHT:
		track_piece = new Straight();
		break;

	case TrackPiece::Tag::RIGHT_TURN: 
		track_piece = new RightTurn();
		break;

	case TrackPiece::Tag::LEFT_TURN:
		track_piece = new LeftTurn();
		break;

	case TrackPiece::Tag::CLIMB_UP:
		track_piece = new ClimbUp();
		break;

	case TrackPiece::Tag::CLIMB_DOWN:
		track_piece = new ClimbDown();
		break;

	case TrackPiece::Tag::LOOP:
		track_piece = new Loop();
		break;

	case TrackPiece::Tag::COMPLETE_TRACK:
		track_piece = new CompleteTrack(spline_controller_->JoinSelf());
		break;

	case TrackPiece::Tag::UNDO:
		RemoveBack();
		break;
	}

	if (CreateTrackPiece(track_piece))
	{
		//	Recalculate t_ boundaries for each piece.
		CalculatePieceBoundaries();
	}
}

//	For each track piece, calculate the values of t at the start and the end of the track piece.
void Track::CalculatePieceBoundaries()
{
	float length_to = 0.0f;
	for (int i = 0; i < track_pieces_.size(); i++)
	{
		track_pieces_[i]->bounding_values_.t0 = spline_controller_->GetTimeAtDistance(length_to / spline_controller_->GetArcLength());
		length_to += track_pieces_[i]->GetLength();
		track_pieces_[i]->bounding_values_.t1 = spline_controller_->GetTimeAtDistance(length_to / spline_controller_->GetArcLength());
	}
}

//	Calculate the frame of reference at the point t.
void Track::Update(float t)
{
	if (track_pieces_.size() == 0)
	{
		return;
	}

	t_ = spline_controller_->GetTimeAtDistance(t);

	int active_index = GetActiveTrackPiece();
	TrackPiece* active_track_piece = track_pieces_.at(active_index);

	forward_ = spline_controller_->GetTangent(t_);
	right_ = up_.Cross(forward_).Normalised();
	up_ = forward_.Cross(right_).Normalised();

	//	The start and target roll for this timestep.
	float start_roll = 0.0f;
	if ((track_pieces_.size() > 1) && (active_index > 0 ))
	{
		start_roll = track_pieces_.at(active_index - 1)->GetRollTarget();
	}

	//	Scale t between t0 and t1 for this track piece to be between 0 and 1;
	float roll_time = (t_ - active_track_piece->bounding_values_.t0) / (active_track_piece->bounding_values_.t1 - active_track_piece->bounding_values_.t0);
	float target_roll = Lerpf(start_roll * 0.0174533f, active_track_piece->GetRollTarget() * 0.0174533f, roll_time);

	//	Get the difference between the desired roll and the current roll.
	float angle_needed = target_roll - roll_;
	
	if (angle_needed != 0.0f)
	{
		SL::Matrix3x3 roll_matrix;
		roll_matrix.RotationAxisAngle(forward_, angle_needed);

		up_ = roll_matrix.TransformVector(up_);

		right_ = up_.Cross(forward_);

		roll_ = target_roll;
	}
}

//	Binary search for track piece that t lies on.
int Track::GetActiveTrackPiece()
{
	int mid = 0;
	int left = 0;
	int right = track_pieces_.size();

	while (left <= right)
	{
		mid = (left + right) / 2;

		if ((track_pieces_[mid]->bounding_values_.t0 <= t_) && (track_pieces_[mid]->bounding_values_.t1 >= t_))
		{
			return mid;
		}

		if (track_pieces_[mid]->bounding_values_.t0 > t_)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return mid;
}

DirectX::XMFLOAT3 Track::GetPointAtDistance(float d)
{
	SL::Vector point;

	if (track_pieces_.size() != 0)
	{
		point = spline_controller_->GetPointAtDistance(d);
	}

	return XMFLOAT3(point.X(), point.Y(), point.Z());
}

DirectX::XMFLOAT3 Track::GetPoint()
{
	SL::Vector point;
	
	if (track_pieces_.size() != 0)
	{
		point = spline_controller_->GetPoint(t_);
	}

	return XMFLOAT3(point.X(), point.Y(), point.Z());
}

DirectX::XMFLOAT3 Track::GetForward()
{
	return XMFLOAT3(forward_.X(), forward_.Y(), forward_.Z());
}

DirectX::XMFLOAT3 Track::GetUp()
{
	return XMFLOAT3(up_.X(), up_.Y(), up_.Z());
}

DirectX::XMFLOAT3 Track::GetRight()
{
	return XMFLOAT3(right_.X(), right_.Y(), right_.Z());
}

float Track::Lerpf(float f0, float f1, float t)
{
	return (1.0f - t) * f0 + t * f1;
}

Track::~Track()
{
	for (int i = 0; i < track_pieces_.size(); i++)
	{
		if (track_pieces_[i])
		{
			delete track_pieces_[i];
			track_pieces_[i] = 0;
		}
	}

	if (spline_controller_)
	{
		delete spline_controller_;
		spline_controller_ = 0;
	}

	if (spline_mesh_)
	{
		delete spline_mesh_;
		spline_mesh_ = 0;
	}
}