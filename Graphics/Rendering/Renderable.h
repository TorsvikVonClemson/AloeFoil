#pragma once
#include <stdio.h> 
#include <iostream>
#include <vector>

#include <SDL.h> 
#include <SDL_image.h>
#include <string>
class Renderable
{
public:
	Renderable(std::string path, SDL_Renderer* renderer,int screeWidth,int screenHeight);
	~Renderable();
	SDL_Texture* getRenderable();
	void modulateColour(Uint8 red, Uint8 green, Uint8 blue );


private:
	SDL_Texture* m_NewTexture = NULL;
	std::vector<SDL_Rect*> sprite;
	int m_Width,m_Height;
	int m_ScreenWidth, m_ScreenHeight;
	int m_GridWidth, m_GridHeight;

};