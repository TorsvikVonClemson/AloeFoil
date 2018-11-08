#include "hexagon.h"

Hexagon::Hexagon(int width, int height, Window* window, Renderer* renderer)
{
	srand(time(NULL));

	m_ScreenX = width;
	m_ScreenY = height;
	m_Rot = 0;
	m_PosX = 0;
	m_PosY = 0;
	m_AnimationTimer = 16;
	m_Window = window;
	m_Renderer = renderer;

}

void Hexagon::drawHexagon(double size, int centX, int centY, Uint8 red, Uint8 green, Uint8 blue)
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

void Hexagon::drawHexGrid(double size,int radius, int centOffsetX, int centOffsetY)
{
	//Draws a hex grid of variable radius and size. Runs 60 fps ate Size=20 and Radius=100

	//Clockwise. Starting at 12
	for (int i = -radius; i <= radius ; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			for (int k = -radius; k <= radius; k++)
			{
				if (i + j + k==0)
				{
					int centX = m_ScreenX / 2;
					int centY = m_ScreenY / 2;
					int offsetX = (i*size*sin(1.0472) - k*size*sin(1.0472));
					int offsetY = 1.5*j*size;
					centX += offsetX + centOffsetX;
					centY += offsetY + centOffsetY;
					//if statement only renders things in range an on screen.
					if (((abs(i) - 1)*size*sin(1.0472)) < m_ScreenX && (((abs(j) - 1)*size*1.5) < m_ScreenY/2 + abs(centOffsetY)) && ((abs(k) - 1)*size*sin(1.0472) < m_ScreenX))
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
