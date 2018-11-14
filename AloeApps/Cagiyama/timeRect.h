#pragma once

class TimeRect
{
public:
	TimeRect(int quarters, int frames);
	~TimeRect();
	float getQ();
	float getF();

private:
	int m_Q, m_Frames;
};