#include "timedCounter.h"

TimedCounter::TimedCounter(int width, int height, Window* window, Renderer* renderer)
{
	m_Width = width;
	m_Height = height;
	m_Window = window;
	m_Renderer = renderer;

	SDL_SetRenderDrawBlendMode(m_Renderer->getRenderer(), SDL_BLENDMODE_BLEND);

	m_Font = new TrueType(renderer);
	m_Font->setFont("AloeApps/Cagiyama/Media/MasterSystem.ttf", 50);

	m_Native = new Native(width, height, renderer);
}

TimedCounter::~TimedCounter()
{
}

void TimedCounter::run(int frame)
{
	float x,y,w,h;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	Uint8 r = 0x17;
	Uint8 g = 0x56;
	Uint8 b = 0x9B;

	m_KeyPressed = m_Window->getKeyPressed();

	//Failures
	if (GetAsyncKeyState(0x6D) && !m_FailHeld) {
		m_FailHeld = true;
		m_FailCount++;
		failRect.push_back(TimeRect(m_FailCount, frame));
	}
	else if (!GetAsyncKeyState(0x6D) && m_FailHeld) {
		m_FailHeld = false;
	}
	else if (m_FailHeld) { r = 0xFF; g = 0x00; b = 0xFF; }
	else{}

	//Retrys
	if ((GetAsyncKeyState(0x6A)||(GetAsyncKeyState(0x52) && GetAsyncKeyState(0x11))) && !m_RetryHeld) {
		m_RetryHeld = true;
		m_RetryCount++;
		retryRect.push_back(TimeRect(m_RetryCount, frame));
	}
	else if (!GetAsyncKeyState(0x6A)&& !GetAsyncKeyState(0x52) && !GetAsyncKeyState(0x11) && m_RetryHeld) {
		m_RetryHeld = false;
	}
	else if (m_RetryHeld) { r = 0x00; g = 0xFF; b = 0x00; }
	else {}

	//Fail>Retry
	if (m_FailCount>=m_RetryCount)
	{
		r = 0x17;
		g = 0x56;
		b = 0x9B;
		for (int i = 0; i < failRect.size(); i++) {
			w = m_Width*(failRect[i].getF() / frame);
			x = m_Width - w;
			h = m_Height*((m_FailCount - failRect[i].getQ() + 1) / (m_FailCount + 1));
			y = m_Height - h;
			m_Native->transRect(x, y, w, h, r, g, b, 0x88);
		}
		r = 0xFF;
		g = 0x00;
		b = 0x00;
		for (int i = 0; i < retryRect.size(); i++) {
			w = m_Width*(retryRect[i].getF() / frame);
			x = m_Width - w;
			h = m_Height*((m_RetryCount - failRect[i].getQ() + 1) / (m_FailCount + 1));
			y = m_Height - h;
			m_Native->transRect(x, y, w, h, r, g, b, 0x88);
		}
	}

	//Fail<Retry
	else if (m_FailCount < m_RetryCount)
	{
		r = 0xFF;
		g = 0x00;
		b = 0x00;
		for (int i = 0; i < retryRect.size(); i++) {
			w = m_Width*(retryRect[i].getF() / frame);
			x = m_Width - w;
			h = m_Height*((m_RetryCount - retryRect[i].getQ() + 1) / (m_RetryCount + 1));
			y = m_Height - h;
			m_Native->transRect(x, y, w, h, r, g, b, 0x88);
		}
		r = 0x17;
		g = 0x56;
		b = 0x9B;
		for (int i = 0; i < failRect.size(); i++) {
			w = m_Width*(failRect[i].getF() / frame);
			x = m_Width - w;
			h = m_Height*((m_FailCount - retryRect[i].getQ() + 1) / (m_RetryCount + 1));
			y = m_Height - h;
			m_Native->transRect(x, y, w, h, r, g, b, 0x88);
		}
	}


	//std::string count = "$" + std::to_string(m_TimedCount / 4);
	//if (m_TimedCount % 4 !=0){count = count + "." + std::to_string(m_TimedCount % 4 * 25); }	
	std::string count = std::to_string(m_FailCount) +" Deaths";
	m_Font->loadFromRenderedText(count, textColor, 0, 0, 0, NULL, 0, NULL, SDL_FLIP_NONE);
	int yOff= m_Font->getHeight();

	count = std::to_string(m_RetryCount) + " Attempts";
	m_Font->loadFromRenderedText(count, textColor, 0, yOff, 0, NULL, 0, NULL, SDL_FLIP_NONE);

	float QC = m_FailCount;
	//std::string dph = "$'s per Hour: " + std::to_string(((QC/4)*60*60*60) / (frame));
	std::string dph = "Deaths per hr: " + std::to_string(((QC)*60*60*60) / (frame));
	m_Font->loadFromRenderedText(dph, textColor, m_Width/3, 0, 0, NULL, 0, NULL, SDL_FLIP_NONE);
}
