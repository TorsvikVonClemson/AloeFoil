#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
{
	//Initialize Renderer
	//m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Initialize Renderer Colour
		//SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0xAA, 0xFF);
		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);

		//Initialize PNGs
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags)&imgFlags))
		{
			printf("SDL_image failed to initialize! SDL_image Error: %s\n", IMG_GetError());
		}

		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = NULL;

	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = NULL;

	IMG_Quit();
}

void Renderer::display()
{
	SDL_RenderPresent(m_Renderer);
}

void Renderer::clear()
{
	SDL_RenderClear(m_Renderer);
}

void Renderer::render(int x, int y,SDL_Texture* texture, SDL_Rect * sprite,SDL_Rect* viewPort,double angle,SDL_Point* center,SDL_RendererFlip flip)
{

	SDL_RenderSetViewport(m_Renderer, viewPort);

	SDL_Rect renderQuad = { x,y,m_Width,m_Height };

	if (sprite != NULL)
	{
		renderQuad.w = sprite->w;
		renderQuad.h = sprite->h;
	}

	SDL_RenderCopyEx(m_Renderer,texture, sprite, &renderQuad,angle,center,flip);
}

SDL_Renderer * Renderer::getRenderer()
{
	return m_Renderer;
}

void Renderer::setViewPort(SDL_Texture* texture, int width,int height)
{
	SDL_Rect bottomRightViewport;
	bottomRightViewport.x = width/2;
	bottomRightViewport.y = height/2;
	bottomRightViewport.w = width / 2;
	bottomRightViewport.h = height / 2;

	SDL_RenderSetViewport(m_Renderer, &bottomRightViewport);

	SDL_RenderCopy(m_Renderer, texture, NULL, NULL);
}

void Renderer::setLayer(SDL_Texture * texture, int layer)
{
	if (texture == NULL)
	{
		printf("Failed to load texture image!\n");
	}

	if (layer==0)
	{
			m_Layer0 = texture;
	}
	else if (layer == 1)
	{
		m_Layer1 = texture;
	}
	else if (layer == 2)
	{
		m_Layer2 = texture;
	}

}


bool Renderer::init()
{
	return false;
}


SDL_Texture* Renderer::loadTexture(std::string path)
{

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load Image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Delete old surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}