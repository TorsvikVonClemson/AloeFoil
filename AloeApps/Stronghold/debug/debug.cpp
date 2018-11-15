#include "debug.h"

Debug::Debug(int width, int height, Renderer* renderer,Window* window)
{
	m_Renderer = renderer;
	m_HexSize = 20;
	m_BoardRadius = 20;
	m_Mode = 0;
	m_Width = width;
	m_Height = height;
	m_Window = window;

	//define sprite sheet
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_Sprite[i + j * 10].x = 20 * i;
			m_Sprite[i + j * 10].y = 20 * j;
			m_Sprite[i + j * 10].w = 20;
			m_Sprite[i + j * 10].h = 20;
		}
	}

	m_SEGAFont = new TrueType(renderer);
	m_SEGAFont->setFont("AloeApps/StrongHold/Media/NiseSega.ttf", 35);

	m_ConsoleFont = new TrueType(renderer);
	m_ConsoleFont->setFont("AloeApps/StrongHold/Media/lucon.ttf", 15);

	m_ImaginaryGrid = new Grid(m_BoardRadius,m_Window,m_Renderer,m_Renderable,m_ViewPort);

	m_Native = new Native(width, height, renderer);

	m_Renderable = new Renderable("AloeApps/StrongHold/Media/HexSprites.png", renderer->getRenderer(), width, height);

	m_CentOffsetX = 0;
	m_CentOffsetY = 0;

}

Debug::~Debug()
{
	delete m_SEGAFont;
	delete m_ConsoleFont;
	delete m_ImaginaryGrid;
	delete m_Native;
	delete m_Renderable;
	std::cout << "Debug DELETED!" << std::endl;
}

int Debug::run()
{
	m_Scene = 1;
	switch (m_Mode) {
	case 0:
		mode0();
		break;
	case 1:
		mode1();
		break;
	case 2:
		mode2();
		break;
	case 3:
		mode3();
		break;
	case 4:
		mode4();
		break;
	case 5:
		mode5();
		break;
	}

	m_Delay -= 1;
	borderMenu();
	return m_Scene;
}

void Debug::keyboard()
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

	if (m_KeyPressed[SDL_SCANCODE_KP_MINUS] && m_Delay <= 0)
	{
		if (m_Mode == 0) { m_Mode = 5; }
		else { m_Mode -= 1; }
		m_Delay = 10;
	}
	if (m_KeyPressed[SDL_SCANCODE_KP_PLUS] && m_Delay <= 0)
	{
		if (m_Mode == 5) { m_Mode = 0; }
		else { m_Mode += 1; }
		m_Delay = 10;
	}

	if (m_KeyPressed[SDL_SCANCODE_1]) { m_Value = 1; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_2]) { m_Value = 2; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_3]) { m_Value = 3; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_4]) { m_Value = 4; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_5]) { m_Value = 5; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_6]) { m_Value = 6; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_7]) { m_Value = 7; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_8]) { m_Value = 8; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_9]) { m_Value = 9; m_ImaginaryGrid->clearGrid(); }
	if (m_KeyPressed[SDL_SCANCODE_0]) { m_Value = 0; m_ImaginaryGrid->clearGrid(); }

	if (m_KeyPressed[SDL_SCANCODE_SPACE] && m_Delay <= 0) { m_SpaceSwitch = !m_SpaceSwitch; m_Delay = 10; }

	if (m_KeyPressed[SDL_SCANCODE_ESCAPE])
	{
		m_Scene = 0;
		//std::cout << "ESCAPE!"<< std::endl;
	}

}

void Debug::borderMenu()
{
	std::string text;
	int textOffsetX = 10;
	int textOffsetY = 15;

	//Top Border Menu
	m_Native->fillRect(0, 0, 6 * m_Width / 8, m_Height / 8, 0x00, 0x00, 0x00);
	for (int i = 0; i < 8; i++) { m_Native->rect(i, i, (6 * m_Width / 8) - (2 * i), (m_Height / 8) - (2 * i), 0xFF - (i * 0x20), 0xFF - (i * 0x20), 0xFF - (i * 0x20)); }

	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

	text = "Mode:";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetX += 10 + m_SEGAFont->getWidth();


	//Right Border Menu
	m_Native->fillRect(6 * m_Width / 8, 0, 2 * m_Width / 8, m_Height, 0x00, 0x00, 0x00);
	for (int i = 0; i < 8; i++) { m_Native->rect((6 * m_Width / 8) + i, i, (2 * m_Width / 8) - (2 * i), m_Height - (2 * i), 0xFF - (i * 0x20), 0xFF - (i * 0x20), 0xFF - (i * 0x20)); }


	switch (m_Mode) {
	case 0:
		mode0Menu(textOffsetX, textOffsetY, (2 * m_Width / 8) - (2 * 8));
		break;
	case 1:
		mode1Menu(textOffsetX, textOffsetY, (2 * m_Width / 8) - (2 * 8));
		break;
	case 2:
		mode2Menu(textOffsetX, textOffsetY, (2 * m_Width / 8) - (2 * 8));
		break;
	case 3:
		mode3Menu(textOffsetX, textOffsetY, (2 * m_Width / 8) - (2 * 8));
		break;
	case 4:
		mode4Menu(textOffsetX, textOffsetY, (2 * m_Width / 8) - (2 * 8));
		break;
	case 5:
		mode5Menu(textOffsetX, textOffsetY, (2 * m_Width / 8) - (2 * 8));
		break;
	}

}

void Debug::mode0()	//Print a hex grid of variable size
{
	m_Native->drawHexGrid(m_HexSize, m_BoardRadius, 0, 0);

	keyboard();
}

void Debug::mode0Menu(int textOffsetX, int textOffsetY, int boxWidth)
{

	std::string text;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };


	text = "Blank Grid";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);


	textOffsetX = 10 + 6 * m_Width / 8;
	textOffsetY = 10;

	//Right Border
	text = "Simply prints a grid.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

}

void Debug::mode1()	//Place a cursor loced to mouse position
{
	m_Native->drawHexagon(m_HexSize, m_Window->getMousePosX(), m_Window->getMousePosY(), 0x00, 0x00, 0xFF);

	keyboard();
}

void Debug::mode1Menu(int textOffsetX, int textOffsetY, int boxWidth)
{
	std::string text;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

	text = "Cursor";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);

	textOffsetX = 10 + 6 * m_Width / 8;
	textOffsetY = 10;

	//Right Border
	text = "Cursor on the mouse.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

}

void Debug::mode2()	//Lock a cursor to a grid
{
	m_Native->drawHexGrid(m_HexSize, m_BoardRadius, 0, 0);
	for (int i = -m_BoardRadius; i <= m_BoardRadius; i++)
	{
		for (int j = -m_BoardRadius; j <= m_BoardRadius; j++)
		{
			for (int k = -m_BoardRadius; k <= m_BoardRadius; k++)
			{
				if ((i + j + k == 0) && (m_Window->getMousePosY() > (1.5*j*m_HexSize + m_Height / 2) - (m_HexSize*.7)) && (m_Window->getMousePosY() < (1.5*j*m_HexSize + m_Height / 2) + (m_HexSize*.7)) && (m_Window->getMousePosX() < (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) + (m_Width / 2) + (m_HexSize*.7)) && (m_Window->getMousePosX() > (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) + (m_Width / 2) - (m_HexSize*.7)))
				{
					m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)), 1.5*j*m_HexSize + m_Height / 2, 0xFF, 0x00, 0x00);
				}
			}
		}
	}

	keyboard();
}

void Debug::mode2Menu(int textOffsetX, int textOffsetY, int boxWidth)
{
	std::string text;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

	text = "Locked Cursor";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);

	textOffsetX = 10 + 6 * m_Width / 8;
	textOffsetY = 10;

	//Right Border
	text = "Prints a cursor to the mouse, bound to the grid.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();
}

void Debug::mode3() //Pathfind between a selected grid and the cursor. An outdated experimental method.
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
				if ((i + j + k == 0) && (m_Window->getMousePosX()<6 * m_Width / 8) && (m_Window->getMousePosY()>m_Height / 8) && (m_Window->getMousePosY() > (1.5*j*m_HexSize - m_CentOffsetY + m_Height / 2) - (m_HexSize*.7)) && (m_Window->getMousePosY() < (1.5*j*m_HexSize - m_CentOffsetY + m_Height / 2) + (m_HexSize*.7)) && (m_Window->getMousePosX() < (i*m_HexSize*sin(1.0472) - m_CentOffsetX - k*m_HexSize*sin(1.0472)) + (m_Width / 2) + (m_HexSize*.7)) && (m_Window->getMousePosX() > (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) - m_CentOffsetX + (m_Width / 2) - (m_HexSize*.7)))
				{
					if (m_Window->getMouseButton() && !m_MouseHeld && (m_CursorPos[0] != i || m_CursorPos[1] != j || m_CursorPos[2] != k))
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
					else if (!m_Window->getMouseButton() && m_MouseHeld)
					{
						//revalidate the mouse
						m_MouseHeld = false;
					}
					else
					{
						if (m_CursorPos[0] + m_CursorPos[1] + m_CursorPos[2] != 3)
						{
							//if there is a selected hex; pathfind
							while (m_CursorPos[0] != i + vi || m_CursorPos[1] != j + vj || m_CursorPos[2] != k + vk)
							{
								//move NE
								if (m_CursorPos[0] > i + vi && m_CursorPos[1] < j + vj)
								{
									vi += 1;
									vj -= 1;
									m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
								}

								//move E
								else if (m_CursorPos[0] > i + vi && m_CursorPos[2] < k + vk)
								{
									vi += 1;
									vk -= 1;
									m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
								}

								//move SE
								if (m_CursorPos[1] > j + vj && m_CursorPos[2] < k + vk)
								{
									vj += 1;
									vk -= 1;
									m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
								}

								//move SW
								if (m_CursorPos[0] < i + vi && m_CursorPos[1] > j + vj)
								{
									vi -= 1;
									vj += 1;
									m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
								}

								//move W
								if (m_CursorPos[0] < i + vi && m_CursorPos[2] > k + vk)
								{
									vi -= 1;
									vk += 1;
									m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
								}

								//move NW
								if (m_CursorPos[1] < j + vj && m_CursorPos[2] > k + vk)
								{
									vj -= 1;
									vk += 1;
									m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + ((i + vi)*m_HexSize*sin(1.0472) - (k + vk)*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*(j + vj)*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0xFF);
								}
							}
							m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*j*m_HexSize + m_Height / 2 - m_CentOffsetY, 0x00, 0xFF, 0x00);
						}
						else
						{
							//if there is no selected hex
							m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + (i*m_HexSize*sin(1.0472) - k*m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*j*m_HexSize + m_Height / 2 - m_CentOffsetY, 0xFF, 0x00, 0x00);

						}
					}
				}
			}
		}
	}
	//draw the selected hex
	if (m_CursorPos[0] + m_CursorPos[1] + m_CursorPos[2] != 3) { m_Native->drawHexagon(m_HexSize*.75, (m_Width / 2) + (m_CursorPos[0] * m_HexSize*sin(1.0472) - m_CursorPos[2] * m_HexSize*sin(1.0472)) - m_CentOffsetX, 1.5*m_CursorPos[1] * m_HexSize + m_Height / 2 - m_CentOffsetY, 0xFF, 0xFF, 0x00); }

	m_Native->drawHexGrid(m_HexSize, m_BoardRadius, -m_CentOffsetX, -m_CentOffsetY);

	keyboard();
}

void Debug::mode3Menu(int textOffsetX, int textOffsetY, int boxWidth)
{
	std::string text;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

	text = "Basic Pathfind";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);

	textOffsetX = 10 + 6 * m_Width / 8;
	textOffsetY = 10;

	//Right Border
	text = "Select a hex. A basic path will be found between the selected hex and the cursor.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();
}

void Debug::mode4()
{
	int vi = 0;
	int vj = 0;
	int vk = 0;

	m_ImaginaryGrid->printGrid(m_Value, m_CentOffsetX, m_CentOffsetY,m_Native,m_HexSize,m_Width,m_Height);

	m_MouseHeld = m_ImaginaryGrid->cursorGrid(m_Width, m_Height, m_Value+25, m_MouseHeld, m_CentOffsetX, m_CentOffsetY, m_HexSize,m_SpaceSwitch);

	m_ImaginaryGrid->bloom(m_Value);

	m_Native->drawHexGrid(m_HexSize, m_BoardRadius, m_CentOffsetX, m_CentOffsetY);

	keyboard();

}

void Debug::mode4Menu(int textOffsetX, int textOffsetY, int boxWidth)
{
	std::string text;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

	text = "Bloom";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);

	textOffsetX = 10 + 6 * m_Width / 8;
	textOffsetY = 10;

	//Right Border
	text = "Select a hex. A radius will expand from the center.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

	text = "A pretense to pathfinding.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

	text = "Use numbers 0-9 to change radius.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();
}

void Debug::mode5()
{
	int vi = 0;
	int vj = 0;
	int vk = 0;
	bool paintMode = m_SpaceSwitch;

	
	m_ImaginaryGrid->printGrid(m_Value, m_CentOffsetX, m_CentOffsetY, m_Native, m_HexSize, m_Width, m_Height);

	m_ImaginaryGrid->clearGrid();
	m_ImaginaryGrid->printObjectGrid(m_Value, m_CentOffsetX, m_CentOffsetY, m_Native, m_HexSize, m_Width, m_Height);
	m_ImaginaryGrid->clearOverlayGrid();

	m_MouseHeld = m_ImaginaryGrid->cursorGrid(m_Width, m_Height, m_Value, m_MouseHeld, m_CentOffsetX, m_CentOffsetY, m_HexSize,m_SpaceSwitch);

	m_ImaginaryGrid->heuristicBloom(m_Value);

	m_ImaginaryGrid->findPath();

	m_Native->drawHexGrid(m_HexSize, m_BoardRadius, -m_CentOffsetX, -m_CentOffsetY);

	keyboard();

}

void Debug::mode5Menu(int textOffsetX, int textOffsetY, int boxWidth)
{
	std::string text;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

	text = "Heuristic Bloom";
	m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);

	textOffsetX = 10 + 6 * m_Width / 8;
	textOffsetY = 10;

	//Right Border
	text = "Select a hex. A radius will expand from the center favoring the current cursor position.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

	text = "Press [SPACE] to switch to the object painter.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

	text = "Use numbers 0-4 to change severity.";
	m_ConsoleFont->loadFromRenderedText(text, textColor, textOffsetX, textOffsetY, boxWidth, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetY += 10 + m_ConsoleFont->getHeight();

	//Bottom
	m_Native->fillRect(0, m_Height-(m_Height/8), 6 * m_Width / 8, m_Height / 8, 0x00, 0x00, 0x00);
	for (int i = 0; i < 8; i++) { m_Native->rect(i, i+ m_Height - (m_Height / 8), (6 * m_Width / 8) - (2 * i), (m_Height / 8) - (2 * i), 0xFF - (i * 0x20), 0xFF - (i * 0x20), 0xFF - (i * 0x20)); }

	text = "Painting ->";
	m_SEGAFont->loadFromRenderedText(text, textColor, 10, m_Height - (m_Height / 8)+12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
	textOffsetX = 10 + m_SEGAFont->getWidth();

	if (!m_SpaceSwitch)
	{
		text = "Center";
		textColor = { 0x00, 0xFF, 0x00 };
		m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, m_Height - (m_Height / 8) + 12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
	}
	else
	{
		switch (m_Value) 
		{
		case 0:
			text = "Deleting";
			textColor = { 0x8F, 0x8F, 0x8F };
			m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, m_Height - (m_Height / 8) + 12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
			break;
		case 1:
			text = "Level 1";
			textColor = { 0xFF, 0xFF, 0x00 };
			m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, m_Height - (m_Height / 8) + 12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
			break;
		case 2:
			text = "Level 2";
			textColor = { 0xFF, 0x8F, 0x00 };
			m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, m_Height - (m_Height / 8) + 12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
			break;
		case 3:
			text = "Level 3";
			textColor = { 0xFF, 0x00, 0x00 };
			m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, m_Height - (m_Height / 8) + 12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
			break;
		case 4:
			text = "Blocking";
			textColor = { 0xFF, 0xFF, 0xFF };
			m_SEGAFont->loadFromRenderedText(text, textColor, textOffsetX, m_Height - (m_Height / 8) + 12, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
			break;
		}
	}

}