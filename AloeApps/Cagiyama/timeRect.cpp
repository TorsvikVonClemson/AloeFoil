#include "timeRect.h"

TimeRect::TimeRect(int quarters, int frames)
{
	m_Q = quarters;m_Frames = frames;
}

TimeRect::~TimeRect()
{
}

float TimeRect::getQ()
{
	return m_Q;
}

float TimeRect::getF()
{
	return m_Frames;
}
