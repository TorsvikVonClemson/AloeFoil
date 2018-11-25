#pragma once

#include "../../../Tools/music.h"

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();
	void play();
	int musicRoom();

private:
	int m_BGMTrack=0;

	Music *m_Music = NULL;

};
