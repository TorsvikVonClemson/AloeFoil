#include "musicPlayer.h"

MusicPlayer::MusicPlayer()
{
	m_Music = new Music();
}

void MusicPlayer::play()
{
	m_Music->loadMusic();
}

int MusicPlayer::musicRoom()
{
	play();

	return 3;
}
