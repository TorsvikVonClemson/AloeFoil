#pragma once

#include <stdio.h> 
#include <iostream>

#include "../Window/window.h"
#include "../Rendering/Renderable.h"
#include "../Rendering/Renderer.h"
#include "../Natives/native.h"
#include <SDL.h> 

#include <string>
#include <time.h>

class Hexagon
{
public:
	Hexagon(int width, int height, Window* window, Renderer* renderer);
	void Hexagon::drawHexagon(double size, int centX,int centY,Uint8 red,Uint8 green, Uint8 blue);
	void drawHexGrid(double size, int radius,int centOffsetX,int centOffsetY);


private:
	int m_ScreenX;
	int m_ScreenY;
	int m_InputTimer;
	int m_AnimationTimer;
	int m_MoveState = 0;
	double m_Rot;
	int m_PosX, m_PosY;
	const Uint8* m_KeyPressed = NULL;


	Window* m_Window = NULL;
	Renderer* m_Renderer = NULL;
	SDL_Texture* m_Renderable = NULL;
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
};