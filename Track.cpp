#include "Track.h"

#include "SplineMesh.h"
#include "RightTurn.h"
#include "Straight.h"
#include "LeftTurn.h"
#include "ClimbUp.h"
#include "ClimbDown.h"

Track::Track(const int resolution, SplineMesh* spline_mesh) : resolution_(resolution), spline_mesh_(spline_mesh)
{
	spline_controller_ = new SL::CRSplineController(resolution);
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

	}

	if (segment)
	{
		track_pieces_.push_back(segment);
		spline_controller_->AddSegment(segment->GetSpline(), 1.0f, true);

		if (spline_mesh_)
		{
			spline_mesh_->Update(spline_controller_);
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
