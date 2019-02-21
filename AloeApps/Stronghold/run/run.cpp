#include "run.h"

Run::Run(int width, int height, Window * window, Renderer * renderer)
{
	m_Width = width;
	m_Height = height;

	m_Window = window;
	m_Renderer = renderer;

}

void Run::controlSwitcher()
{
	switch (m_State)
	{
		case 0:
			if (m_Debug != NULL) { delete m_Debug; m_Debug = NULL; }
			if (m_GameMap != NULL) { delete m_GameMap; m_GameMap = NULL; }
			if (m_Title == NULL)
			{
				m_Title=new Title(m_Width,m_Height,m_Renderer,m_Window);
			}
			else
			{
				m_State=(m_Title->run());
			}
			break;
		case 1:
			if (m_Title != NULL) { delete m_Title; m_Title = NULL; }
			if (m_Debug == NULL)
			{
				m_Debug = new Debug(m_Width, m_Height, m_Renderer,m_Window);
			}
			else
			{
				m_State = (m_Debug->run());
			}
			break;
		case 2:
			if (m_Title != NULL) { delete m_Title; m_Title = NULL; }
			if (m_GameMap == NULL)
			{
				m_GameMap= new GameMap(m_Width, m_Height, m_Renderer, m_Window);
			}
			else
			{
				m_State = (m_GameMap->run());
			}
			break;
		case 3:
			if (m_Title != NULL) { delete m_Title; m_Title = NULL; }
			if (m_MusicPlayer == NULL)
			{
				m_MusicPlayer = new MusicPlayer(m_Width, m_Height, m_Renderer, m_Window);
			}
			else
			{
				m_State = (m_MusicPlayer->musicRoom());
			}
			break;
	}
}
