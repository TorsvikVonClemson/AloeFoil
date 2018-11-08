#pragma once
#include <stdio.h> 
#include <iostream>

#include "../Graphics/Window/window.h"
#include "../Graphics/Rendering/Renderable.h"
#include "../Graphics/Rendering/Renderer.h"
#include "../Graphics/Natives/native.h"
#include <SDL.h> 

#include <string>
#include <time.h>

class Hosono
{
public:
	Hosono(int width, int height);
	void run(Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void playfield(Window* window);
	void moveCursorUp(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorUpLeft(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorUpRight(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorDown(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorDownLeft(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorDownRight(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorLeft(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);
	void moveCursorRight(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport);

private:
	int m_ScreenX;
	int m_ScreenY;
	int m_InputTimer;
	int m_AnimationTimer;
	int m_MoveState = 0;
	double m_Rot;
	int m_PosX, m_PosY;
	const Uint8* m_KeyPressed = NULL;


	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;
	SDL_Texture* m_Renderable = NULL;
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;

	SDL_Rect m_sprite[100];
	int m_matrix[1200];

};