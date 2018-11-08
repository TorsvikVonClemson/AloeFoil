#include "gameBoard.h"

GameBoard::GameBoard(int width, int height, Window* window,Hexagon * hex, double hexSize, int boardRadius)
{
	m_Hex = hex;
	m_HexSize = hexSize;
	m_BoardRadius = boardRadius;
	m_Window = window;
	m_Width = width;
	m_Height = height;

	m_CentOffsetX = 0;
	m_CentOffsetY = 0;
}

void GameBoard::debug(int mode)
{
	if (mode == 0) //just print the grid
	{
		m_Hex->drawHexGrid(m_HexSize, m_BoardRadius,0,0);
	}

	if (mode == 1)//have a hex follow the cursor
	{
		m_Hex->drawHexagon(m_HexSize, m_Window->getMousePosX(), m_Window->getMousePosY(), 0x00, 0x00, 0xFF);
	}

	if (mode == 2)//have a hex cursor lock to a grid follow the cursor
	{
		m_Hex->drawHexGrid(m_HexSize, m_BoardRadius,0,0);
		for (int i = -m_BoardRadius; i <= m_BoardRadius; i++)
		{
			for (int j = -m_BoardRadius; j <= m_BoardRadius; j++)
			{
				for (int k = -m_BoardRadius; k <= m_BoardRadius; k++)
				{
					if ((i + j + k == 0) && (m_Window->getMousePosY() > (1.5*j*m_HexSize + m_Height/2)-(m_HexSize*.7)) && (m_Window->getMousePosY() < (1.5*j*m_HexSize + m_Height / 2)+ (m_HexSize*.7)) && (m_Window->getMousePosX() < (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) +(m_Width/2) + (m_HexSize*.7)) && (m_Window->getMousePosX() > (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) + (m_Width/2) - (m_HexSize*.7)))
					{
						m_Hex->drawHexagon(m_HexSize*.75, (m_Width/2)+(i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)), 1.5*j*m_HexSize + m_Height / 2, 0xFF, 0x00, 0x00);
					}
				}
			}
		}
	}

	if (mode == 3)
	{


		//state for controls while on the playfield

		m_KeyPressed = m_Window->getKeyPressed();

		//Clockwise starting from 1 at 12

		if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY -= 5;}
		if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY -= 5, m_CentOffsetX += 5;}
		if (!m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetX += 5;}
		if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY += 5, m_CentOffsetX += 5; }
		if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY += 5; }
		if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY += 5, m_CentOffsetX -= 5;}
		if (!m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetX -= 5; }
		if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_CentOffsetY -= 5, m_CentOffsetX -= 5;}

		m_Hex->drawHexGrid(m_HexSize,m_BoardRadius,-m_CentOffsetX,-m_CentOffsetY);
	}

	if (mode == 4) 		//Hex pathfinding
	{
		int vi = 0;
		int vj = 0;
		int vk = 0;
		for (int i = -m_BoardRadius; i <= m_BoardRadius; i++)
		{
			for (int j = -m_BoardRadius; j <= m_BoardRadius; j++)
			{
				for (int k = -m_BoardRadius; k <= m_BoardRadius; k++)
				{
					if ((i + j + k == 0) && (m_Window->getMousePosY() > (1.5*j*m_HexSize - m_CentOffsetY + m_Height / 2) - (m_HexSize*.7)) && (m_Window->getMousePosY() < (1.5*j*m_HexSize - m_CentOffsetY + m_Height / 2) + (m_HexSize*.7)) && (m_Window->getMousePosX() < (i*m_HexSize*sin(1.0472) - m_CentOffsetX - k*m_HexSize*sin(1.0472)) + (m_Width / 2) + (m_HexSize*.7)) && (m_Window->getMousePosX() > (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) - m_CentOffsetX + (m_Width / 2) - (m_HexSize*.7)))
					{
						if (m_Window->getMouseButton() && !m_MouseHeld && (m_CursorPos[0]!=i || m_CursorPos[1] != j || m_CursorPos[2] != k))
						{
							//if there is no selected hex and the mouse is valid
							m_CursorPos[0] = i;
							m_CursorPos[1] = j;
							m_CursorPos[2] = k;
							m_MouseHeld = true;
						}
						else if (m_Window->getMouseButton() && !m_MouseHeld && m_CursorPos[0] == i && m_CursorPos[1] == j && m_CursorPos[2] == k)
						{
							//de-select a hex while the mouse is valid
							m_CursorPos[0] = 1;
							m_CursorPos[1] = 1;
							m_CursorPos[2] = 1;
							m_MouseHeld = true;
						}
						else if (!m_Window->getMouseButton()&&m_MouseHeld) 
						{
							//revalidate the mouse
							m_MouseHeld = false; 
						}
						else 
						{ 
							if (m_CursorPos[0] + m_CursorPos[1] + m_CursorPos[2] != 3)
							{
								//if there is a selected hex; pathfind
								while (m_CursorPos[0] != i + vi || m_CursorPos[1] != j + vj || m_CursorPos[2] != k+vk)
								{
									//move NE
									if (m_CursorPos[0] > i+vi && m_CursorPos[1] < j+vj)
									{
										vi += 1;
										vj -= 1;
										m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i+vi)*m_HexSize*sin(1.0472) - (k+vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j+vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
									}

									//move E
									else if (m_CursorPos[0] > i + vi && m_CursorPos[2] < k + vk)
									{
										vi += 1;
										vk -= 1;
										m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i+vi)*m_HexSize*sin(1.0472) - (k+vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j+vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
									}

									//move SE
									if (m_CursorPos[1] > j + vj && m_CursorPos[2] < k + vk)
									{
										vj += 1;
										vk -= 1;
										m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
									}

									//move SW
									if (m_CursorPos[0] < i + vi && m_CursorPos[1] > j + vj)
									{
										vi -= 1;
										vj += 1;
										m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
									}

									//move W
									if (m_CursorPos[0] < i + vi && m_CursorPos[2] > k + vk)
									{
										vi -= 1;
										vk += 1;
										m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
									}

									//move NW
									if (m_CursorPos[1] < j + vj && m_CursorPos[2] > k + vk)
									{
										vj -= 1;
										vk += 1;
										m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
									}
								}
								m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*j*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0x00);
							}
							else
							{
								//if there is no selected hex
								m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*j*m_HexSize + m_Height / 2 - m_CentOffsetY, 0xFF, 0x00, 0x00);
							
							}
						}
					}
				}
			}
		}
		//draw the selected hex
		if (m_CursorPos[0] + m_CursorPos[1] + m_CursorPos[2] !=3) { m_Hex->drawHexagon(m_HexSize*.75, (m_Width / 2) + (m_CursorPos[0] * m_HexSize*sin(1.0472) - m_CursorPos[2] * m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*m_CursorPos[1] * m_HexSize + m_Height / 2 - m_CentOffsetY, 0xFF, 0xFF, 0x00); }

		m_KeyPressed = m_Window->getKeyPressed();


		m_Hex->drawHexGrid(m_HexSize, m_BoardRadius, -m_CentOffsetX, -m_CentOffsetY);

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
	return;
}
