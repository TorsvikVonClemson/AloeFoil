#pragma once
#include <stdio.h> 
#include <iostream>
#include <algorithm>
#include <iterator>

#include "../Graphics/Window/window.h"
#include "../Graphics/Rendering/Renderable.h"
#include "../Graphics/Rendering/Renderer.h"
#include "../Graphics/Natives/native.h"
#include <SDL.h> 

#include <string>
#include <time.h>

class MapTest
{
public:
	MapTest(int width, int height);
	void run(Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void northSouthRiver();
	void perimeterFill(int X, int Y, int* matrixAffected, int* matrixChecked, int newVal);
	void elementFill(int* matrixAffected, int* matrixChecked, int valid, int low, int med, int high);
	void perimeterCheck(int X, int Y,int* matrixAffected, int* matrixChecked, int newVal, int failVal);
	void emptyFailMat();
private:
	int m_ScreenX;
	int m_ScreenY;
	int m_TilesX;
	int m_TilesY;

	int m_matrix[1200];
	int m_RiverMatrix[1200];
	int m_FailVals[10];
	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;
	SDL_Texture* m_Renderable = NULL;

	SDL_Rect m_sprite[100];

};