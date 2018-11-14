#pragma once

#include <vector>
#include "Windows.h"

#include "..\..\Graphics\Window\window.h"
#include "..\..\Graphics\Rendering\Renderer.h"
#include "..\..\Graphics\Rendering\trueType.h"
#include "..\..\Graphics\Natives\native.h"

#include "timeRect.h"

/*
A small program that reads how many times I've pressed Ctrl+r and makes a graph from it.
I'm gonna try to keep this contained all in one class so that it might eventually becoem part of a larger multi tool.
*/

class TimedCounter
{
public:
	TimedCounter(int width,int height, Window* window, Renderer* renderer);
	~TimedCounter();
	void run(int frame);
private:
	int m_Width;
	int m_Height;	
	int m_FailCount = 0;
	int m_RetryCount = 0;

	bool m_FailHeld = false;
	bool m_RetryHeld = false;

	const Uint8* m_KeyPressed = NULL;

	Window* m_Window = NULL;
	Renderer* m_Renderer = NULL;
	TrueType* m_Font = NULL;
	Native* m_Native = NULL;
	
	std::vector<TimeRect> failRect;
	std::vector<TimeRect> retryRect;
};