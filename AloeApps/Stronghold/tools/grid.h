#pragma once

#include <algorithm>
#include <time.h>

#include "..\..\Graphics\Natives\native.h"
#include "..\..\Graphics\Window\window.h"
#include "..\..\Graphics\Rendering\Renderable.h"
#include "..\..\maths.h"

class Grid
{
public:
	Grid(int boardRadius, Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* viewPort);
	~Grid();
	void clearGrid(int boardRadius);
	void clearObjectGrid(int boardRadius);
	void clearOverlayGrid(int boardRadius);
	void printGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height);
	void printObjectGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height);
	void renderGrids(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height);
	void renderObjectGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height);
	void renderOverlayGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height);
	void draw(int i, int j, int k, Uint8 red, Uint8 green, Uint8 blue,int xOff, int yOff, Native* native, int hexSize, int width, int height);
	void bloom(int radius, int boardRadius);
	void heuristicBloom(int radius, int boardRadius);
	bool cursorGrid(int width, int height, int radius, int boardRadius, bool mouseHeld, int xOff, int yOff, int hexSize, bool stateSwitch);
	void setCursor(int value);

	void randomizeGrid(int boardRadius);
	void rollRivers(int boardRadius);
	void expandGrid(int boardRadius);
	void cleanGrid(int boardRadius);
	void chooseRiver(int i, int j, int k, int xPos, int yPos);
	void chooseCoast(int i, int j, int k, int xPos, int yPos);

	int gridEffect(int i, int j, int k, int step);
	void findPath();

	int getRiverDirection();

private:
	int m_GridLayeri[50][50][50];	//imaginary layer
	int m_GridLayer0[50][50][50];	//bkgrn layer
	int m_GridLayer1[50][50][50];	//river layer
	int m_GridLayer2[50][50][50];	//terrain layer
	int m_Grid[50][50][50];
	int m_ObjectGrid[50][50][50];
	int m_OverlayGrid[50][50][50];
	int m_CursorPos[3] = { 1,1,1 };
	int m_SelectedHex[3] = { 1,1,1 };
	int m_RiverDirection = 0;

	SDL_Rect m_sprite[100];

	Window* m_Window = NULL;
	Renderer* m_Renderer = NULL;
	Renderable* m_Renderable = NULL;
	SDL_Rect* m_ViewPort=NULL;
	Maths* m_Maths=NULL;
};