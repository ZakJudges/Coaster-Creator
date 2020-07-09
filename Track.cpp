#include "Track.h"

#include "SplineMesh.h"
#include "RightTurn.h"
#include "Straight.h"
#include "LeftTurn.h"
#include "ClimbUp.h"
#include "ClimbDown.h"
#include "CompleteTrack.h"

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

	spline_controller_->RemoveBack();

	TrackPiece* piece_to_remove = track_pieces_.back();
	if (piece_to_remove)
	{
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
	TrackPiece* segment = nullptr;

	switch (tag)
	{
	case TrackPiece::Tag::STRAIGHT:
		segment = new Straight();
		break;

	case TrackPiece::Tag::RIGHT_TURN: 
		segment = new RightTurn();
		break;

	case TrackPiece::Tag::LEFT_TURN:
		segment = new LeftTurn();
		break;

	case TrackPiece::Tag::CLIMB_UP:
		segment = new ClimbUp();
		break;

	case TrackPiece::Tag::CLIMB_DOWN:
		segment = new ClimbDown();
		break;

	case TrackPiece::Tag::COMPLETE_TRACK:
		segment = new CompleteTrack(spline_controller_->JoinSelf());
		break;

	case TrackPiece::Tag::UNDO:
		RemoveBack();
		break;

	}

	if (segment)
	{
		if (spline_controller_->AddSegment(segment->GetSpline(), 1.0f, segment->ShouldSmooth()))
		{
			track_pieces_.push_back(segment);
			if (spline_mesh_)
			{
				spline_mesh_->Update(spline_controller_);
			}
		}
		else
		{
			//	Segment could not be added to the spline.
			delete segment;
			segment = 0;
		}
	}
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
