#include "TrackPreview.h"

#include "TrackPiece.h"
#include "TrackMesh.h"


TrackPreview::TrackPreview(TrackMesh* track_mesh) : track_mesh_(track_mesh)
{
    t_ = 0.0f;
    track_piece_ = new TrackPiece();

    SL::CRSpline* spline_segment = new SL::CRSpline();
    SL::Vector p0, p1, p2, p3;

    p0.Set(0.0f, 0.0f, 0.0f);
    p1.Set(0.0f, 0.0f, 0.0f);
    p2.Set(0.0f, 0.0f, 0.0f);
    p3.Set(0.0f, 0.0f, 0.0f);

    spline_segment->SetControlPoints(p0, p1, p2, p3);
    track_piece_->SetSplineSegment(spline_segment);

    spline_controller_ = new SL::CRSplineController(100);

    spline_controller_->AddSegment(spline_segment, 1.0f);
}

//  Copy the track piece that has just been created.
void TrackPreview::InitTrackPiece(TrackPiece* track_piece)
{
    //  Make the preview track piece identical to the newly placed track piece.
    SL::Vector p0 = track_piece->GetControlPoint(0);
    SL::Vector p1 = track_piece->GetControlPoint(1);
    SL::Vector p2 = track_piece->GetControlPoint(2);
    SL::Vector p3 = track_piece->GetControlPoint(3);
    track_piece_->SetControlPoints(p0, p1, p2, p3);

    track_piece_->SetTension(track_piece->GetTension());
    track_piece_->SetRollTarget(track_piece->GetRollTarget());

    track_piece_->CalculateSpline();

    spline_controller_->CalculateSplineLength();

    up_ = track_piece->GetInitUp();
    initial_up_ = up_;

    right_ = track_piece->GetInitRight();
    initial_right_ = right_;

    forward_ = track_piece->GetInitForward();
    initial_forward_ = forward_;
}

void TrackPreview::GenerateMesh()
{
    //  Simulate this track piece, given the initial conditions from the main track.
    //  Use the simulation to generate the points for the mesh.
}

void TrackPreview::UpdateSimulation(float t)
{
  
}

TrackPiece* TrackPreview::GetPreviewPiece()
{
    return track_piece_;
}

TrackPreview::~TrackPreview()
{
    if (track_piece_)
    {
        delete track_piece_;
        track_piece_ = nullptr;
    }
    
    if (spline_controller_)
    {
        delete spline_controller_;
        spline_controller_ = 0;
    }
}
