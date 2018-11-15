#pragma once

#include <stdio.h> 
#include <iostream>

#include "..\..\Graphics\Natives\native.h"
#include "..\..\Graphics\Window\window.h"
#include "..\..\Graphics\Rendering\trueType.h"
#include "..\..\Graphics\Rendering\Renderable.h"
#include "..\tools\grid.h"

#include <string>
#include <time.h>

class Debug
{
public:
	Debug(int width, int height, Renderer* renderer, Window* window);
	~Debug();
	int run();
	void keyboard();
	void borderMenu();

	//Dunno if I want to make these into seperate classes or what. They've gotten kinda big
	void mode0();
	void mode0Menu(int textOffsetX, int textOffsetY, int boxWidth);
	void mode1();
	void mode1Menu(int textOffsetX, int textOffsetY, int boxWidth);
	void mode2();
	void mode2Menu(int textOffsetX, int textOffsetY, int boxWidth);
	void mode3();
	void mode3Menu(int textOffsetX, int textOffsetY, int boxWidth);
	void mode4();
	void mode4Menu(int textOffsetX, int textOffsetY, int boxWidth);
	void mode5();
	void mode5Menu(int textOffsetX, int textOffsetY, int boxWidth);

private:
	int m_BoardRadius;
	int m_Delay = 0;
	int m_Value = 0;
	int m_Width;
	int m_Height;
	int m_Mode;
	int m_CentOffsetX;
	int m_CentOffsetY;
	int m_Scene = 1;

	int m_CursorPos[3] = { 1,1,1 };

	double m_HexSize;

	bool m_SpaceSwitch = false;
	bool m_MouseHeld = false;

	const Uint8* m_KeyPressed = NULL;

	SDL_Rect m_Sprite[100];
	Window* m_Window = NULL;
	Renderer* m_Renderer = NULL;
	Renderable* m_Renderable = NULL;
	SDL_Rect* m_ViewPort=NULL;
	Native* m_Native = NULL;
	TrueType* m_SEGAFont = NULL;
	TrueType* m_ConsoleFont = NULL;
	Grid* m_ImaginaryGrid = NULL;

};