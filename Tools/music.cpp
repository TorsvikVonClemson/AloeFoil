#include "music.h"

Music::Music()
{
	bool success=true;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError()); success = false; }
}

void Music::loadMusic()
{
	m_Music = Mix_LoadMUS("Media/Bionic Leviathan.wav");
	if (m_Music == NULL)
	{
		printf("Failed to load music!");
	}
	Mix_PlayMusic(m_Music, -1);
}
