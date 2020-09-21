#pragma once

#include "Track.h"

class TrackLoader
{
public:
	bool SaveTrack(char file_name[], Track* track);
	bool LoadTrack(char* file_name, Track* track);
private:
};