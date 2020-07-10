#include "Track.h"

#include "SplineMesh.h"
#include "RightTurn.h"
#include "Straight.h"
#include "LeftTurn.h"
#include "ClimbUp.h"
#include "ClimbDown.h"
#include "CompleteTrack.h"
#include "Loop.h"

Track::Track(const int resolution, SplineMesh* spline_mesh) : resolution_(resolution), spline_mesh_(spline_mesh)
{
	spline_controller_ = new SL::CRSplineController(resolution);
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

	if (track_piece)
	{
		for (int i = 0; i < track_piece->GetNumberOfSplines(); i++)
		{
			if (spline_controller_->AddSegment(track_piece->GetSpline(i), 1.0f, track_piece->ShouldSmooth()))
			{
				//	Spline successfully added to the spline controller.

				//	TODO: Track if ALL of the splines that make up this track piece were added to the spline controller successfully.
			}
			else
			{
				//	Segment could not be added to the spline.
				delete track_piece;
				track_piece = 0;
				break;
			}
		}

		track_pieces_.push_back(track_piece);

		if (spline_mesh_)
		{
			spline_mesh_->Update(spline_controller_);
		}
	}
}

DirectX::XMVECTOR Track::GetPointAtTime(const float t)
{
	SL::Vector point = spline_controller_->GetPointAtDistance(t);
	
	return DirectX::XMVectorSet(point.X(), point.Y(), point.Z(), 0.0f);
}

DirectX::XMFLOAT3 Track::GetForward(const float t)
{
	SL::Vector forward = spline_controller_->GetTangent(t);

	return DirectX::XMFLOAT3(forward.X(), forward.Y(), forward.Z());
}

DirectX::XMFLOAT3 Track::GetUp(const float t)
{
	SL::Vector up = spline_controller_->GetNormal(t);

	return DirectX::XMFLOAT3(up.X(), up.Y(), up.Z());
}

DirectX::XMFLOAT3 Track::GetRight(const float t)
{
	SL::Vector right = spline_controller_->GetBiTangent(t);

	return DirectX::XMFLOAT3(right.X(), right.Y(), right.Z());
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
