#pragma once

class Track;

class TrackLoader
{
public:
	TrackLoader();
	bool SaveTrack(char file_name[], Track* track);
	bool LoadTrack(char* file_name, Track* track);
private:
	const unsigned int floats_per_segment_;
};