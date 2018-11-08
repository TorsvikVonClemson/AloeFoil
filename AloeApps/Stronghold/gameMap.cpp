#include "gameMap.h"

GameMap::GameMap(int width, int height, Renderer * renderer, Window * window)
{
	m_Renderer = renderer;
	m_HexSize = 20;
	m_BoardRadius = 20;
	m_Width = width;
	m_Height = height;
	m_Window = window;


	m_ViewPort.x = 0;
	m_ViewPort.y = 0;
	m_ViewPort.w= m_Width;
	m_ViewPort.h = m_Height;
	//define sprite sheet
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

	m_Native = new Native(width, height, renderer);

	m_Renderable = new Renderable("Media/HexSprites.png", renderer->getRenderer(), width, height);

	m_Grid = new Grid(m_BoardRadius, m_Window,m_Renderer,m_Renderable,&m_ViewPort);

	m_CentOffsetX = 0;
	m_CentOffsetY = 0;
}

int GameMap::run()
{
	int vi = 0;
	int vj = 0;
	int vk = 0;

	if (m_Randomize) { m_Grid->randomizeGrid(m_BoardRadius); m_Randomize = false; }

	//m_ImaginaryGrid->printObjectGrid(m_Value, m_BoardRadius, 0x00, 0x00, 0x00, m_CentOffsetX, m_CentOffsetY, m_Native, m_HexSize, m_Width, m_Height);
	m_Grid->renderGrids(m_Pace, m_BoardRadius, 0x00, 0x00, 0x00, m_CentOffsetX, m_CentOffsetY, m_Native, m_HexSize, m_Width, m_Height);
	//m_ImaginaryGrid->printGrid(m_Value, m_BoardRadius, 0x00, 0x00, 0x00, m_CentOffsetX, m_CentOffsetY, m_Native, m_HexSize, m_Width, m_Height);

	m_Grid->clearGrid(m_BoardRadius);
	m_Grid->clearOverlayGrid(m_BoardRadius);

	//m_MouseHeld = m_Grid->cursorGrid(m_Width, m_Height, m_Pace, m_BoardRadius, m_MouseHeld, m_CentOffsetX, m_CentOffsetY, m_HexSize, m_SpaceSwitch);

	m_Grid->heuristicBloom(10, m_BoardRadius);

	m_Grid->findPath();

	SDL_RenderSetScale((m_Renderer)->getRenderer(), 2, 2);
	m_Renderer->render((m_Width/2)-m_Sprite[0].w, 0, m_Renderable->getRenderable(), &m_Sprite[4], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render((m_Width / 2) - m_Sprite[0].w, 0, m_Renderable->getRenderable(), &m_Sprite[5], &m_ViewPort, m_Grid->getRiverDirection(), NULL, SDL_FLIP_NONE);
	SDL_RenderSetScale((m_Renderer)->getRenderer(), 1, 1);

	keyboard();

	return 2;
}

void GameMap::keyboard()
{
	m_KeyPressed = m_Window->getKeyPressed();

	//Clockwise starting from 1 at 12

	if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY -= 5; }
	if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY -= 5, m_CentOffsetX += 5; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetX += 5; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY += 5, m_CentOffsetX += 5; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY += 5; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY += 5, m_CentOffsetX -= 5; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetX -= 5; }
	if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY -= 5, m_CentOffsetX -= 5; }

}
