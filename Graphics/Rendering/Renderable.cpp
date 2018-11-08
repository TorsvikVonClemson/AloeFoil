#include "Renderable.h"

Renderable::Renderable(std::string path, SDL_Renderer * renderer, int screeWidth, int screenHeight)
{
	m_ScreenWidth = screeWidth;
	m_ScreenHeight = screenHeight;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load Image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//set chromakey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0x00));
		//create texture from surface pixels
		m_NewTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (m_NewTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//set image dimensions
		m_Width = loadedSurface->w;
		m_Height = loadedSurface->h;

		//Delete old surface
		SDL_FreeSurface(loadedSurface);
	}
}

Renderable::~Renderable()
{
	SDL_DestroyTexture(m_NewTexture); 
	m_NewTexture = NULL;
}

SDL_Texture* Renderable::getRenderable()
{
	return m_NewTexture;
}

void Renderable::modulateColour(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_NewTexture, red, green, blue);
}
