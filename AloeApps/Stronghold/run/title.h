#pragma once

#include <string>
#include <iostream>

#include "..\..\Graphics\Window\window.h"
#include "..\..\Graphics\Rendering\Renderable.h"
#include "..\..\Graphics\Rendering\Renderer.h"
#include "..\..\Graphics\Rendering\trueType.h"
#include "..\..\Tools\maths.h"

class Title
{
public:
	Title(int width, int height,Renderer* renderer,Window* window);
	~Title();
	int run();
	bool front();
	int menu();
	bool button(Window* window, int xMin, int xMax, int yMin, int yMax);
	bool label(int xPos,int yPos,int xWidth,int yHeight, std::string text);
private:
	int m_Width;
	int m_Height;
	int m_Frame = 0;
	int m_HalfFrame = 0;
	int m_State=0;

	bool m_Highlight = false;
	bool m_MouseHeld = false;

	SDL_Rect m_Sprite[100];
	SDL_Rect m_SSprite[100];
	SDL_Rect m_ViewPort;

	Renderer* m_Renderer = NULL;
	Renderable* m_SpriteSheet = NULL;
	Renderable* m_MootSheet = NULL;
	Window* m_Window = NULL;
	TrueType* m_SEGAFont = NULL;
	Maths* m_Maths = NULL;
};