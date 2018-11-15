#pragma once
#include <SDL.h> 
#include <SDL_mixer.h> 
#include <stdio.h> 
#include <string>

class Music
{
public:
	Music();
	void loadMusic();
private:
	Mix_Music *m_Music = NULL;
};