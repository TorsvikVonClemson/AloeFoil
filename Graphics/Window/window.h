#pragma once
#include <stdio.h> 
#include <iostream>

#include "mouse.h"
#include "timer.h"

#include <SDL.h> 
#include <SDL_image.h>
#include <string>
class Window 
{
public:
	Window(const char *title,int width,int height);
	~Window();
	SDL_Window* getWindow();
	const Uint8* getKeyPressed();
	int getWidth();
	int getMousePosX();
	int getMousePosY();
	int getFrame();
	bool getMouseButton();
	bool isClosed();
	void setFrame(int f);
	void close();
	void update();

	SDL_Surface* loadSurface(const char *image);

	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL

	};
private:
	bool init();

	const char *m_Title = NULL;
	int m_Width;
	int m_Height;
	int m_MousePosX=0;
	int m_MousePosY=0;
	int m_CurrentFrame = 0;
	float m_AvgFPS = 0;
	bool m_MouseDown = false;
	bool m_IsClosed = false;



	std::string m_path = "StrongestFairy.png";
	const Uint8* m_CurrentKeyStates = SDL_GetKeyboardState(NULL);
	Mouse m_Mouse;

	SDL_Event e;
	SDL_Window* m_Window = NULL;
	SDL_Surface* m_ScreenSurface = NULL;
	SDL_Surface* m_ImageMedia = NULL;
	SDL_Surface* m_CurrentSurface = NULL;
	//SDL_Surface* m_KeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
	Timer* m_Ticks;
	Timer* m_Frames;

};
