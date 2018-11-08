#pragma once
#include <stdio.h> 
#include <iostream>

#include "../Graphics/Window/window.h"
#include "../Graphics/Rendering/Renderable.h"
#include "../Graphics/Rendering/Renderer.h"
#include "../Graphics/Natives/native.h"
#include <SDL.h> 

#include <string>
#include <time.h>

class SheetTest
{
public:
	SheetTest(int width,int height);
	void run(Window* window, Renderer* renderer, Renderable* renderable,SDL_Rect* viewport);
private:
	int m_ScreenX;
	int m_ScreenY;
	double m_Rot;

	SDL_Window* m_Window=NULL;
	SDL_Renderer* m_Renderer = NULL;
	SDL_Texture* m_Renderable = NULL;

	SDL_Rect m_sprite[100];
	int m_matrix[1200];

};