#include "TrackLoader.h"

#include <iostream>
#include <fstream>

TrackLoader::TrackLoader() : lines_per_segment_(7)
{

}

bool TrackLoader::LoadTrack(char* file_name, Track* track)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        //  Get the data from the file and pass to the track object.
        while (!file.eof())
        {

        }

        file.close();

        return true;
    }
    return false;
}

bool TrackLoader::SaveTrack(char file_name[], Track* track)
{
    std::ofstream file(file_name);
    if (file.is_open())
    {
        //  Loop through each track piece and input track data to file.
        for (int i = 0; i < track->GetTrackPieceCount(); i++)
        {
            TrackPiece* piece = track->GetTrackPiece(i);
            SL::Vector point = piece->GetControlPoint(0);
            file << point.X() << point.Y() << point.Z() << std::endl;
            point = piece->GetControlPoint(1);
            file << point.X() << point.Y() << point.Z() << std::endl;
            point = piece->GetControlPoint(2);
            file << point.X() << point.Y() << point.Z() << std::endl;
            point = piece->GetControlPoint(3);
            file << point.X() << point.Y() << point.Z() << std::endl;
            file << piece->GetTension() << std::endl;
            file << piece->GetRollTarget() << std::endl;
            file << piece->GetLength() << std::endl << std::endl;
        }

        file.close();

        return true;
    }
    return false;
}
