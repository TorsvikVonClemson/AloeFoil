#pragma once

#include "Renderer.h"

#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_ttf.h> 
#include <stdio.h> 
#include <string> 
#include <cmath>

class TrueType
{
public:
	TrueType(Renderer* renderer);
	~TrueType();
	bool loadFromFile(std::string path);//load file from specifc path
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, int x, int y,int width, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);//Creates image from font string																			//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void free();

	void setFont(std::string path,int size);

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* m_Texture;

	int m_Width;
	int m_Height;
	std::string m_Text;
	std::string m_Path;

	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;
	TTF_Font* m_Font = NULL;

};