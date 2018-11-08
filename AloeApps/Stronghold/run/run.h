#pragma once

#include "..\..\Graphics\Window\window.h"
#include "..\..\Graphics\Rendering\Renderer.h"
#include "title.h"
#include "..\debug\debug.h"
#include "..\gameMap.h"

class Run
{
public:
	Run(int width, int height, Window* window, Renderer* renderer);
	void controlSwitcher();
private:
	int m_State = 0;
	int m_Width;
	int m_Height;

	bool m_TitleExists = false;

	Window* m_Window = NULL;
	Renderer* m_Renderer = NULL;
	SDL_Rect* m_ViewPort = NULL;
	Title* m_Title = NULL;
	Debug* m_Debug = NULL;
	GameMap* m_GameMap = NULL;
};