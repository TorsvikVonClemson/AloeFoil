#pragma once

#include "..\Rendering\Renderer.h"

#include <SDL.h> 


class Native {
public:
	Native(int width,int height, Renderer* renderer);
	~Native();
	void testRect();
	void rect(int x, int y, int w, int h, Uint8 red, Uint8 green, Uint8 blue);
	void fillRect(int x, int y, int w, int h, Uint8 red, Uint8 green, Uint8 blue);
	void drawHexagon(double size, int centX, int centY, Uint8 red, Uint8 green, Uint8 blue);
	void drawHexGrid(double size, int radius, int centOffsetX, int centOffsetY);

private:
	int m_width, m_height;
	Renderer* m_Renderer;
};