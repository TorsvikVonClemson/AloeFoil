#include "timer.h"


Timer::Timer()
{
	m_StartTicks = 0;
}

void Timer::start()
{
	m_StartTicks = SDL_GetTicks();
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;
	time = SDL_GetTicks() - m_StartTicks;
	return time;
}
