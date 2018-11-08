#include "native.h"

Native::Native(int width, int height, Renderer* renderer)
{
	m_width = width;
	m_height = height;

	m_Renderer = renderer;
}

Native::~Native()
{
}

void Native::testRect()
{
	//fill a red rect
	SDL_Rect fillRect = { m_width / 4, m_height / 4, m_width / 2, m_height / 2 };
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(m_Renderer->getRenderer(), &fillRect);

	//Green Quad
	SDL_Rect outlineRect = { m_width / 6, m_height / 6, m_width * 2 / 3, m_height * 2 / 3 };
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(m_Renderer->getRenderer(), &outlineRect);

	//Blue H Line
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(m_Renderer->getRenderer(), 0, m_height / 2, m_width, m_height / 2);

	//Yellow Dotted V Line
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < m_height; i += 4)
	{
		SDL_RenderDrawPoint(m_Renderer->getRenderer(), m_width / 2, i);
	}

	//Update
	SDL_RenderPresent(m_Renderer->getRenderer());
}

void Native::rect(int x, int y, int w,int h, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Rect outlineRect = { x, y, w, h };
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), red, green, blue, 0xFF);
	SDL_RenderDrawRect(m_Renderer->getRenderer(), &outlineRect);

	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
}

void Native::fillRect(int x, int y, int w, int h, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Rect fillRect = { x, y, w, h};
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), red, green, blue, 0xFF);
	SDL_RenderFillRect(m_Renderer->getRenderer(), &fillRect);

	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
}

void Native::drawHexagon(double size, int centX, int centY, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), red, green, blue, 0xFF);
	SDL_RenderDrawLine(m_Renderer->getRenderer(), centX, centY - size, centX + (size*sin(1.0472)), centY - (size * cos(1.0472)));
	SDL_RenderDrawLine(m_Renderer->getRenderer(), centX + (size * sin(1.0472)), centY - (size * cos(1.0472)), centX + (size * sin(1.0472)), centY + (size * cos(1.0472)));
	SDL_RenderDrawLine(m_Renderer->getRenderer(), centX + (size * sin(1.0472)), centY + (size * cos(1.0472)), centX, centY + size);
	SDL_RenderDrawLine(m_Renderer->getRenderer(), centX, centY + size, centX - (size * sin(1.0472)), centY + (size * cos(1.0472)));
	SDL_RenderDrawLine(m_Renderer->getRenderer(), centX - (size * sin(1.0472)), centY + (size * cos(1.0472)), centX - (size * sin(1.0472)), centY - (size * cos(1.0472)));
	SDL_RenderDrawLine(m_Renderer->getRenderer(), centX - (size * sin(1.0472)), centY - (size * cos(1.0472)), centX, centY - size);

	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
}

void Native::drawHexGrid(double size, int radius, int centOffsetX, int centOffsetY)
{
	//Draws a hex grid of variable radius and size. Runs 60 fps ate Size=20 and Radius=100

	//Clockwise. Starting at 12
	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			for (int k = -radius; k <= radius; k++)
			{
				if (i + j + k == 0)
				{
					int centX = m_width / 2;
					int centY = m_height / 2;
					int offsetX = (i*size*sin(1.0472) - k*size*sin(1.0472));
					int offsetY = 1.5*j*size;
					centX += offsetX + centOffsetX;
					centY += offsetY + centOffsetY;
					//if statement only renders things in range an on screen.
					if (((abs(i) - 1)*size*sin(1.0472)) < m_width && (((abs(j) - 1)*size*1.5) < m_height / 2 + abs(centOffsetY)) && ((abs(k) - 1)*size*sin(1.0472) < m_width))
					{


						SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderDrawLine(m_Renderer->getRenderer(), centX, centY - size, centX + (size*sin(1.0472)), centY - (size * cos(1.0472)));
						SDL_RenderDrawLine(m_Renderer->getRenderer(), centX + (size * sin(1.0472)), centY - (size * cos(1.0472)), centX + (size * sin(1.0472)), centY + (size * cos(1.0472)));
						SDL_RenderDrawLine(m_Renderer->getRenderer(), centX + (size * sin(1.0472)), centY + (size * cos(1.0472)), centX, centY + size);
						SDL_RenderDrawLine(m_Renderer->getRenderer(), centX, centY + size, centX - (size * sin(1.0472)), centY + (size * cos(1.0472)));
						SDL_RenderDrawLine(m_Renderer->getRenderer(), centX - (size * sin(1.0472)), centY + (size * cos(1.0472)), centX - (size * sin(1.0472)), centY - (size * cos(1.0472)));
						SDL_RenderDrawLine(m_Renderer->getRenderer(), centX - (size * sin(1.0472)), centY - (size * cos(1.0472)), centX, centY - size);
					}
				}
			}
		}
	}
	SDL_SetRenderDrawColor(m_Renderer->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
}
