#include "trueType.h"

TrueType::TrueType(Renderer* renderer)
{
	//Initialize
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;

	m_Renderer = renderer->getRenderer();

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

}

TrueType::~TrueType()
{
	TTF_CloseFont(m_Font);
	m_Font = NULL;
	free();
}

bool TrueType::loadFromFile(std::string path)
{
		//Get rid of preexisting texture
		free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				//Get image dimensions
				m_Width = loadedSurface->w;
				m_Height = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		//Return success
		m_Texture = newTexture;
		return m_Texture != NULL;
}

bool TrueType::loadFromRenderedText(std::string textureText, SDL_Color textColor, int x, int y, int width,SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Common format example
	//		text.loadFromRenderedText("Testing...", textColor,0,0,NULL,0,NULL, SDL_FLIP_NONE);

	//Get rid of preexisting texture
	free();

	//printf("Button Name: %s \n", &textureText);

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(m_Font, textureText.c_str(), textColor,width);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);
		if (m_Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_Width = textSurface->w;
			m_Height = textSurface->h;
		}


		//Get rid of old surface
		SDL_FreeSurface(textSurface);

		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, m_Width, m_Height };

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(m_Renderer, m_Texture, clip, &renderQuad, angle, center, flip);
	}

	//Return success
	return m_Texture != NULL;
}

void TrueType::free()
{
	//Free texture if it exists
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void TrueType::setFont(std::string path, int size)
{
	m_Font = TTF_OpenFont(path.c_str(), size);
	if (m_Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void TrueType::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(m_Renderer, m_Texture, clip, &renderQuad, angle, center, flip);
}

int TrueType::getWidth()
{
	return m_Width;
}

int TrueType::getHeight()
{
	return m_Height;
}

void TrueType::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_Texture, red, green, blue);
}

void TrueType::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_Texture, blending);
}

void TrueType::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

