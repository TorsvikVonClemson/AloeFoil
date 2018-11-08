#pragma once

#include <stdio.h> 
#include <iostream>

#include "..\..\Graphics\Natives\native.h"
#include "..\..\Graphics\Window\window.h"
#include "..\..\Graphics\Rendering\trueType.h"
#include "..\..\Graphics\Rendering\Renderable.h"
#include "..\Stronghold\tools\grid.h"

#include <string>
#include <time.h>

class GameMap
{
public:
	GameMap(int width, int height, Renderer* renderer, Window* window);
	~GameMap();
	int run();
	void keyboard();


private:
	int m_Width;
	int m_Height;
	int m_BoardRadius;
	int m_CentOffsetX;
	int m_CentOffsetY;
	int m_Pace = 0;

	double m_HexSize;

	bool m_MouseHeld = false;
	bool m_SpaceSwitch = false;
	bool m_Randomize = true;

	const Uint8* m_KeyPressed = NULL;

	SDL_Rect m_Sprite[100];
	SDL_Rect m_ViewPort;
	Renderer* m_Renderer = NULL;
	Window* m_Window = NULL;
	Native* m_Native = NULL;
	Renderable* m_Renderable = NULL;
	Grid* m_Grid = NULL;

};