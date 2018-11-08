#pragma once

#include "SDL.h"

class Timer
{
public:
	Timer();
	void start();
	Uint32 getTicks();
private:
	Uint32 m_StartTicks;
};