#pragma once
#include <stdio.h> 
#include <iostream>

#include "..\..\Graphics\Natives\hexagon.h"


#include <string>
#include <time.h>

class GameBoard
{
public:
	GameBoard(int width,int height,Window* window,Hexagon* hex,double hexSize, int boardRadius);
	void debug(int mode);

private:
	int m_Width;
	int m_Height;
	int m_MoveState = 0;
	int m_CentOffsetX;
	int m_CentOffsetY;
	int m_CursorPos[3] = { 1,1,1 };
	bool m_MouseHeld = false;

	Window* m_Window = NULL;
	Hexagon* m_Hex=NULL;
	const Uint8* m_KeyPressed = NULL;
	double m_HexSize;
	int m_BoardRadius;

};