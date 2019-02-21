#pragma once
#include <SDL.h> 
#include <SDL_mixer.h> 
#include <stdio.h> 
#include <string>

class Music
{
public:
	Music();
	void loadMusic(std::string text);
	void stop();
private:
	Mix_Music *m_Music = NULL;
};