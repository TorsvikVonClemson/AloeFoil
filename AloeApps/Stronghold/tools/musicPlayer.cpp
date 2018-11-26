#include "musicPlayer.h"

MusicPlayer::MusicPlayer(int width, int height, Renderer* renderer, Window* window)
{
	m_Width = width;
	m_Height = height;
	m_Renderer = renderer;
	m_Window = window;
	m_Music = new Music();

	m_SpriteSheet = new Renderable("AloeApps/StrongHold/Media/ForeverAlphaSTitle.png", renderer->getRenderer(), width, height);

	m_Font = new TrueType(renderer);
	m_Font->setFont("AloeApps/StrongHold/Media/NiseSega.ttf", 70);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_Sprite[i + j * 10].x = 40 * i;
			m_Sprite[i + j * 10].y = 40 * j;
			m_Sprite[i + j * 10].w = 40;
			m_Sprite[i + j * 10].h = 40;
		}
	}

	m_ViewPort.x = 0;
	m_ViewPort.y = 0;
	m_ViewPort.w = width;
	m_ViewPort.h = height;

	m_Button.push_back(Button((m_Width/2)- (m_Sprite[3].w*4.5), m_Sprite[3].h/2,8, 2, 40, "Music",
		m_SpriteSheet, m_Font, m_Window, m_Renderer));
	m_Button.push_back(Button((m_Width / 2) - (m_Sprite[3].w * 7.5), m_Sprite[3].h*3, 14, 2, 40, "XXXX",
		m_SpriteSheet, m_Font, m_Window, m_Renderer));
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::play()
{
	m_Music->loadMusic();
}

int MusicPlayer::musicRoom()
{
	m_Button[0].render(&m_ViewPort);
	m_Button[1].render(&m_ViewPort);
	play();

	return 3;
}
