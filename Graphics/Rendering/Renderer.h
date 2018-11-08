#pragma once

#include <stdio.h> 
#include <iostream>

#include "../Window/window.h"

#include <SDL.h> 
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <string>
class Renderer
{
public:
	Renderer(SDL_Window *window);
	~Renderer();
	void display();
	void clear();
	void render(int x, int y, SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* viewPort, double angle, SDL_Point* center, SDL_RendererFlip flip);
	SDL_Renderer* getRenderer();
	void setViewPort(SDL_Texture* texture, int width,int height);
	void setLayer(SDL_Texture* texture, int layer);

private:
	bool init();
	int m_Width, m_Height;
	SDL_Texture* loadTexture(std::string path);
	SDL_Texture* m_Texture = NULL;
	SDL_Texture* m_Layer0 = NULL;
	SDL_Texture* m_Layer1 = NULL;
	SDL_Texture* m_Layer2 = NULL;
	SDL_Renderer* m_Renderer = NULL;
};