#include "mouse.h"

Mouse::Mouse()
{
	m_Position.x = 0;
	m_Position.y = 0;
}

void Mouse::setPosition(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Mouse::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y; 
		SDL_GetMouseState(&x, &y);
		setPosition(x, y);

		if (e->type == SDL_MOUSEBUTTONDOWN){ m_MouseDown = true; }
		if (e->type == SDL_MOUSEBUTTONUP) { m_MouseDown = false; }
	}
}

bool Mouse::getButton()
{
	return m_MouseDown;
}

SDL_Point Mouse::getPosition()
{
	return m_Position;
}


