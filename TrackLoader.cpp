#include "TrackLoader.h"

#include <iostream>
#include <fstream>

bool TrackLoader::LoadTrack(char* file_name, Track* track)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        //  Get the data from the file and pass to the track object.

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
        file << 1 << 2 << 3;
        //  Loop through each track piece and input data to file.
        //      Control points.
        //      Tension.
        //      Roll Target.

        file.close();

        return true;
    }
    return false;
}
