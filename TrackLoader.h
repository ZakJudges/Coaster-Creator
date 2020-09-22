#pragma once

#include "Track.h"

class TrackLoader
{
public:
	TrackLoader();
	bool SaveTrack(char file_name[], Track* track);
	bool LoadTrack(char* file_name, Track* track);
private:
	const unsigned int lines_per_segment_;
};