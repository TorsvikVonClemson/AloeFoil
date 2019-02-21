#pragma once

#include "../../../Tools/music.h"
#include "../../../Tools/button.h"
#include "..\..\Graphics\Rendering\trueType.h"

class MusicPlayer
{
public:
	MusicPlayer(int width, int height, Renderer* renderer, Window* window);
	~MusicPlayer();
	void play();
	int musicRoom();

private:
	int m_Width,m_Height, m_BGMTrack=0;

	SDL_Rect m_Sprite[100];
	SDL_Rect m_ViewPort;

	Music *m_Music = NULL;
	Renderer *m_Renderer = NULL;
	Window* m_Window = NULL;
	TrueType* m_Font = NULL;
	Renderable* m_SpriteSheet;

	std::string m_Title[2] = { "BionicLeviathan","SeismicEulogy"};

	std::vector<Button> m_Button;
};
