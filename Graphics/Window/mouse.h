#pragma once

#include <SDL.h>
class Mouse
{
public:
	Mouse();
	void setPosition(int x, int y);
	void handleEvent(SDL_Event* e);
	bool getButton();
	SDL_Point getPosition();

private:
	bool m_MouseDown=false;
	SDL_Point m_Position;
};