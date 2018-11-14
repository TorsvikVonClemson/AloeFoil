#include "grid.h"

Grid::Grid(int boardRadius, Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* m_ViewPort)
{
	clearGrid(boardRadius);
	clearObjectGrid(boardRadius);
	clearOverlayGrid(boardRadius);

	//define sprite sheet
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_sprite[i + j * 10].x = 40 * i;
			m_sprite[i + j * 10].y = 40 * j;
			m_sprite[i + j * 10].w = 40;
			m_sprite[i + j * 10].h = 40;
		}
	}

	m_Window = window;
	m_Renderer = renderer;
	m_Renderable = renderable;

	m_Maths = new Maths();
}

Grid::~Grid()
{
	delete m_Maths;
	std::cout << "Grid DELETED!" << std::endl;

}

void Grid::clearGrid(int boardRadius)
{
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				m_Grid[25 + i][25 + j][25 + k] = 0;
			}
		}
	}
}

void Grid::clearObjectGrid(int boardRadius)
{
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				m_ObjectGrid[25 + i][25 + j][25 + k] = 0;
			}
		}
	}
}

void Grid::clearOverlayGrid(int boardRadius)
{
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				m_OverlayGrid[25 + i][25 + j][25 + k] = 0;
			}
		}
	}
}

void Grid::printGrid(int radius,int boardRadius,Uint8 red,Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height)
{

	//Set Cursor Pos
	//m_Grid[25 + m_CursorPos[0]][25 + m_CursorPos[1]][25 + m_CursorPos[2]] = 1;

	//Set Selected Hex
	m_Grid[25 + m_SelectedHex[0]][25 + m_SelectedHex[1]][25 + m_SelectedHex[2]] = 25;
	
	//print tiles
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (m_Grid[25 + i][25 + j][25 + k] != 0 && i+j+k==0)
				{
					if (m_Grid[25 + i][25 + j][25 + k] == 25)
					{
						red = 0xFF;
						green = 0x00;
						blue = 0xFF;
						draw(i, j, k, red,green,blue, xOff, yOff,native,hexSize,width,height);
					}
					else if (m_Grid[25 + i][25 + j][25 + k] == 99)
					{
						red = 0x00;
						green = 0xFF;
						blue = 0x00;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
					else if(m_Grid[25 + i][25 + j][25 + k] < 25)
					{
						red = 0x00;
						green = 0xFF - (0x40 * (26 + m_Grid[25 + i][25 + j][25 + k]));
						blue = 0xFF;
						draw(i, j, k, red, green, blue,xOff, yOff, native, hexSize, width, height);
					}
					else if (m_Grid[25 + i][25 + j][25 + k] > 99)
					{
						red = 0x00;
						green = 0xFF;
						blue = 0x00;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
				}
			}
		}
	}
	red = 0xFF;
	green = 0x00;
	blue = 0x00;
	draw( m_CursorPos[0], m_CursorPos[1], m_CursorPos[2], red, green, blue, xOff, yOff, native, hexSize, width, height);
}

void Grid::printObjectGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native* native, int hexSize, int width, int height)
{

	//Set Cursor Pos
	//m_ObjectGrid[25 + m_CursorPos[0]][25 + m_CursorPos[1]][25 + m_CursorPos[2]] = 99;

	//print tiles
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (m_ObjectGrid[25 + i][25 + j][25 + k] != 0 && i + j + k == 0)
				{
					if (m_ObjectGrid[25 + i][25 + j][25 + k] == 25)
					{
						red = 0xFF;
						green = 0x00;
						blue = 0xFF;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] == 99)
					{
						red = 0x00;
						green = 0xFF;
						blue = 0x00;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] > 26&& ((m_ObjectGrid[25 + i][25 + j][25 + k]) - 26) % 3!=0 && m_ObjectGrid[25 + i][25 + j][25 + k] < 30)
					{
						red = 0xFF;
						green = 0xFF - (0x80 * (((m_ObjectGrid[25 + i][25 + j][25 + k])-26)%3-1));
						blue = 0x00;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] > 26 && ((m_ObjectGrid[25 + i][25 + j][25 + k]) - 26) % 3 == 0 && m_ObjectGrid[25 + i][25 + j][25 + k] < 30)
					{
						red = 0xFF;
						green = 0x00;
						blue = 0x00;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] == 30)
					{
						red = 0xB0;
						green = 0xB0;
						blue = 0xB0;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] > 99)
					{
						red = 0x00;
						green = 0xFF;
						blue = 0x00;
						draw(i, j, k, red, green, blue, xOff, yOff, native, hexSize, width, height);
					}
				}
			}
		}
	}

	red = 0xFF;
	green = 0x00;
	blue = 0x00;
	draw(25 + m_CursorPos[0], 25 + m_CursorPos[1], 25 + m_CursorPos[2], red, green, blue, xOff, yOff, native, hexSize, width, height);
}

void Grid::renderGrids(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native * native, int hexSize, int width, int height)
{
	//background loop
	//for (int i = 0; i <= width / m_sprite[0].w; i++)
	//{
	//	for (int j = 0; j <= height / m_sprite[0].h; j++)
	//	{
	//		m_Renderer->render(m_sprite[0].w*i, m_sprite[0].h*j, m_Renderable->getRenderable(), &m_sprite[0], *m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	//	}
	//}

	int yPos;
	int xPos;

	//bkgrnd
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					yPos = (1.5*j*hexSize - yOff + height / 2) - 20;
					xPos = i*hexSize*sin(1.0472) - xOff - k*hexSize*sin(1.0472) + (width / 2) - 20;
					m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[0], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
				}
			}
		}
	}

	//Layer 1
	Uint8 surroundingTiles;
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					yPos = (1.5*j*hexSize - yOff + height / 2) - 20;
					xPos = i*hexSize*sin(1.0472) - xOff - k*hexSize*sin(1.0472) + (width / 2) - 20;

					if (m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						chooseRiver(i, j, k, xPos, yPos);
					}
				}
			}
		}
	}

	//Layer 2
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					yPos = (1.5*j*hexSize - yOff + height / 2) - 20;
					xPos = i*hexSize*sin(1.0472) - xOff - k*hexSize*sin(1.0472) + (width / 2) - 20;
					
					
					switch (m_GridLayer2[25 + i][25 + j][25 + k]) {
					case 0:
						break;
					case 27:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[20], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;
					case 28:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[21], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;
					case 29:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[22], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;
					case 30:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[10], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;
					case 33:
						chooseCoast(i,j,k,xPos,yPos);
						break;
					case 34:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[27], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;
					case 35:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[28], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;
					default:
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[6], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
						break;


					}
				}
			}
		}
	}
	

}

void Grid::renderObjectGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native * native, int hexSize, int width, int height)
{
	//background loop
	//for (int i = 0; i <= width / m_sprite[0].w; i++)
	//{
	//	for (int j = 0; j <= height / m_sprite[0].h; j++)
	//	{
	//		m_Renderer->render(m_sprite[0].w*i, m_sprite[0].h*j, m_Renderable->getRenderable(), &m_sprite[0], *m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	//	}
	//}

	int yPos;
	int xPos;

	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					yPos = (1.5*j*hexSize - yOff + height / 2)-20;
					xPos = i*hexSize*sin(1.0472) - xOff - k*hexSize*sin(1.0472)+(width/2)-20;
					if (m_ObjectGrid[25 + i][25 + j][25 + k] == 0)
					{
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[0], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] == 30)
					{
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[10], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] == 29)
					{
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[22], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] == 28)
					{
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[21], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
					}
					else if (m_ObjectGrid[25 + i][25 + j][25 + k] == 27)
					{
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[20], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
					}
				}
			}
		}
	}
}

void Grid::renderOverlayGrid(int radius, int boardRadius, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff, Native * native, int hexSize, int width, int height)
{
	//background loop
	//for (int i = 0; i <= width / m_sprite[0].w; i++)
	//{
	//	for (int j = 0; j <= height / m_sprite[0].h; j++)
	//	{
	//		m_Renderer->render(m_sprite[0].w*i, m_sprite[0].h*j, m_Renderable->getRenderable(), &m_sprite[0], *m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	//	}
	//}

	int yPos;
	int xPos;

	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					yPos = (1.5*j*hexSize - yOff + height / 2) - 20;
					xPos = i*hexSize*sin(1.0472) - xOff - k*hexSize*sin(1.0472) + (width / 2) - 20;
					if (m_OverlayGrid[25 + i][25 + j][25 + k] == 2)
					{
						m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[3], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
					}
				}
			}
		}
	}

	yPos = (1.5*m_CursorPos[1] * hexSize - yOff + height / 2) - 20;
	xPos = m_CursorPos[0] * hexSize*sin(1.0472) - xOff - m_CursorPos[2] * hexSize*sin(1.0472) + (width / 2) - 20;
	m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[1], m_ViewPort, 0, NULL, SDL_FLIP_NONE);

	yPos = (1.5*m_SelectedHex[1] * hexSize - yOff + height / 2) - 20;
	xPos = m_SelectedHex[0] * hexSize*sin(1.0472) - xOff - m_SelectedHex[2] * hexSize*sin(1.0472) + (width / 2) - 20;
	if (m_SelectedHex[0] + m_SelectedHex[1] + m_SelectedHex[2] == 0)
	{
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[2], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	}
	//m_Renderer->render(200, 200, m_Renderable->getRenderable(), &m_sprite[0], *m_ViewPort, 0, NULL, SDL_FLIP_NONE);

}

void Grid::draw(int i, int j, int k, Uint8 red, Uint8 green, Uint8 blue, int xOff, int yOff,Native* native,int hexSize, int width,int height)
{
	native->drawHexagon(hexSize*.75, (width / 2) + (i * hexSize*sin(1.0472) - k * hexSize*sin(1.0472)) - xOff, 1.5*j * hexSize + height / 2 - yOff, red, green, blue);
}

void Grid::bloom(int radius,int boardRadius)
{
	m_Grid[25 + m_SelectedHex[0]][25 + m_SelectedHex[1]][25 + m_SelectedHex[2]] = 25;
	for (int r = 0; r < radius; r++)
	{
		for (int i = -boardRadius; i <= boardRadius; i++)
		{
			for (int j = -boardRadius; j <= boardRadius; j++)
			{
				for (int k = -boardRadius; k <= boardRadius; k++)
				{
					if (m_Grid[25 + i][25 + j][25 + k] == 25-r)
					{
						if (m_Grid[25 + i + 1][25 + j - 1][25 + k] == 0) { m_Grid[25 + i + 1][25 + j - 1][25 + k] = 24-r; }
						if (m_Grid[25 + i + 1][25 + j][25 + k - 1] == 0) { m_Grid[25 + i + 1][25 + j][25 + k - 1] = 24-r; }
						if (m_Grid[25 + i][25 + j + 1][25 + k - 1] == 0) { m_Grid[25 + i][25 + j + 1][25 + k - 1] = 24-r; }
						if (m_Grid[25 + i - 1][25 + j + 1][25 + k] == 0) { m_Grid[25 + i - 1][25 + j + 1][25 + k] = 24-r; }
						if (m_Grid[25 + i - 1][25 + j][25 + k + 1] == 0) { m_Grid[25 + i - 1][25 + j][25 + k + 1] = 24-r; }
						if (m_Grid[25 + i][25 + j - 1][25 + k + 1] == 0) { m_Grid[25 + i][25 + j - 1][25 + k + 1] = 24-r; }
					}
				}
			}
		}
	}
	//std::cout << m_Grid[25 + m_SelectedHex[0] + 1][25 + m_SelectedHex[1] - 1][25 + m_SelectedHex[2]] << std::endl;
	//std::cout << radius << std::endl;
}

void Grid::heuristicBloom(int radius, int boardRadius)
{
	m_Grid[25 + m_SelectedHex[0]][25 + m_SelectedHex[1]][25 + m_SelectedHex[2]] = 25;
	for (int r = 0; r < radius; r++)
	{
		for (int i = -boardRadius; i <= boardRadius; i++)
		{
			for (int j = -boardRadius; j <= boardRadius; j++)
			{
				for (int k = -boardRadius; k <= boardRadius; k++)
				{
					if (m_Grid[25 + i][25 + j][25 + k] == 25 - r)
					{
						if (m_Grid[25 + i + 1][25 + j - 1][25 + k] < 25 - r)
						{
							if (i<m_CursorPos[0] || j>m_CursorPos[1]) { m_Grid[25 + i + 1][25 + j - 1][25 + k] = 24 - r; }
							else if(r+1<radius){ m_Grid[25 + i + 1][25 + j - 1][25 + k] = 24 - r-1; }

							if (m_ObjectGrid[25 + i + 1][25 + j - 1][25 + k] > 25)
							{
								m_Grid[25 + i + 1][25 + j - 1][25 + k] = gridEffect(25 + i + 1, 25 + j - 1, 25 + k, m_Grid[25 + i + 1][25 + j - 1][25 + k]);
							}
						}
						if (m_Grid[25 + i + 1][25 + j][25 + k - 1] < 25 - r)
						{
							if (i<m_CursorPos[0] || k>m_CursorPos[2]) { m_Grid[25 + i + 1][25 + j][25 + k - 1] = 24 - r; }
							else if (r + 1<radius) { m_Grid[25 + i + 1][25 + j][25 + k - 1] = 24 - r - 1; }

							if (m_ObjectGrid[25 + i + 1][25 + j][25 + k-1] > 25)
							{
								m_Grid[25 + i + 1][25 + j][25 + k-1] = gridEffect(25 + i + 1, 25 + j, 25 + k-1, m_Grid[25 + i + 1][25 + j][25 + k-1]);
							}
						}
						if (m_Grid[25 + i][25 + j + 1][25 + k - 1] < 25 - r)
						{
							if (j<m_CursorPos[1] || k>m_CursorPos[2]) { m_Grid[25 + i][25 + j + 1][25 + k - 1] = 24 - r; }
							else if (r + 1<radius) { m_Grid[25 + i][25 + j + 1][25 + k - 1] = 24 - r - 1; }

							if (m_ObjectGrid[25 + i][25 + j + 1][25 + k - 1] > 25)
							{
								m_Grid[25 + i][25 + j + 1][25 + k - 1] = gridEffect(25 + i, 25 + j + 1, 25 + k-1, m_Grid[25 + i][25 + j + 1][25 + k - 1]);
							}
						}
						if (m_Grid[25 + i - 1][25 + j + 1][25 + k] < 25 - r)
						{
							if (i>m_CursorPos[0] || j<m_CursorPos[1]) { m_Grid[25 + i - 1][25 + j + 1][25 + k] = 24 - r; }
							else if (r + 1<radius) { m_Grid[25 + i - 1][25 + j + 1][25 + k] = 24 - r - 1; }

							if (m_ObjectGrid[25 + i - 1][25 + j + 1][25 + k] > 25)
							{
								m_Grid[25 + i - 1][25 + j + 1][25 + k] = gridEffect(25 + i-1, 25 + j + 1, 25 + k, m_Grid[25 + i - 1][25 + j + 1][25 + k]);
							}
						}
						if (m_Grid[25 + i - 1][25 + j][25 + k + 1] < 25 - r)
						{
							if (i>m_CursorPos[0] || k<m_CursorPos[2]) { m_Grid[25 + i - 1][25 + j][25 + k + 1] = 24 - r; }
							else if (r + 1<radius) { m_Grid[25 + i - 1][25 + j][25 + k + 1] = 24 - r - 1; }

							if (m_ObjectGrid[25 + i - 1][25 + j][25 + k + 1] > 25)
							{
								m_Grid[25 + i - 1][25 + j][25 + k + 1] = gridEffect(25 + i - 1, 25 + j, 25 + k+1, m_Grid[25 + i - 1][25 + j][25 + k + 1]);
							}
						}
						if (m_Grid[25 + i][25 + j - 1][25 + k + 1] < 25 - r)
						{
							if (j>m_CursorPos[1] || k<m_CursorPos[2]) { m_Grid[25 + i][25 + j - 1][25 + k + 1] = 24 - r; }
							else if (r + 1<radius) { m_Grid[25 + i][25 + j - 1][25 + k + 1] = 24 - r - 1; }

							if (m_ObjectGrid[25 + i][25 + j - 1][25 + k + 1] > 25)
							{
								m_Grid[25 + i][25 + j - 1][25 + k + 1] = gridEffect(25 + i, 25 + j-1, 25 + k + 1, m_Grid[25 + i][25 + j - 1][25 + k + 1]);
							}
						}
					}
				}
			}
		}
	}
}

bool Grid::cursorGrid(int width,int height,int radius, int boardRadius,bool mouseHeld,int xOff, int yOff,int hexSize,bool stateSwitch)
{
	int xMin = 0;
	int xMax = 0;
	int yMin = 0;
	int yMax = 0;
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				xMin = (i*hexSize*sin(1.0472) - k*hexSize*sin(1.0472)) - xOff + (width / 2) - (hexSize*.7);
				xMax = (i*hexSize*sin(1.0472) - k*hexSize*sin(1.0472)) - xOff + (width / 2) + (hexSize*.7);
				yMin = (1.5*j*hexSize - yOff + height / 2) - (hexSize*.7);
				yMax = (1.5*j*hexSize - yOff + height / 2) + (hexSize*.7);
				/*m_Maths->findRect(m_Window,0,400,0,400)*/

				//if ((i + j + k == 0) && (m_Window->getMousePosX()<6 * width / 8) && (m_Window->getMousePosY()>height / 8) && (m_Window->getMousePosY() > (1.5*j*hexSize - yOff + height / 2) - (hexSize*.7)) && (m_Window->getMousePosY() < (1.5*j*hexSize - yOff + height / 2) + (hexSize*.7)) && (m_Window->getMousePosX() < (i*hexSize*sin(1.0472) - xOff - k*hexSize*sin(1.0472)) + (width / 2) + (hexSize*.7)) && (m_Window->getMousePosX() > (i*hexSize*sin(1.0472) - k*hexSize*sin(1.0472)) - xOff + (width / 2) - (hexSize*.7)))
				if((i + j + k == 0) && (m_Window->getMousePosX()<6 * width / 8) && (m_Window->getMousePosY()>height / 8) && m_Maths->findRect(m_Window, xMin, xMax, yMin, yMax))
				{
					if (m_Window->getMouseButton() && !mouseHeld && (m_SelectedHex[0] != i || m_SelectedHex[1] != j || m_SelectedHex[2] != k))
					{
						//if there is no selected hex and the mouse is valid
						if (!stateSwitch)
						{
							m_SelectedHex[0] = i;
							m_SelectedHex[1] = j;
							m_SelectedHex[2] = k;
							mouseHeld = true;
						}
						else
						{
							if (radius == 0)//delete
							{
								m_ObjectGrid[25 + i][25 + j][25 + k] = 0;
							}
							else
							{
								m_ObjectGrid[25 + i][25 + j][25 + k] = radius + 26;
							}
							
						}


					}
					else if (m_Window->getMouseButton() && !mouseHeld && m_SelectedHex[0] == i && m_SelectedHex[1] == j && m_SelectedHex[2] == k)
					{
						//de-select a hex while the mouse is valid
						m_SelectedHex[0] = 1;
						m_SelectedHex[1] = 1;
						m_SelectedHex[2] = 1;
						mouseHeld = true;
					}
					else if (!m_Window->getMouseButton() && mouseHeld)
					{
						//revalidate the mouse

						mouseHeld = false;
					}
					m_CursorPos[0] = i;
					m_CursorPos[1] = j;
					m_CursorPos[2] = k;
				}
			}
		}
	}
	std::cout << m_SelectedHex[0] << "," << m_SelectedHex[1] << "," << m_SelectedHex[2] /*<< "        " << m_Grid[25 + m_CursorPos[0]][25 + m_CursorPos[1]][25 + m_CursorPos[2]]*/ << std::endl;
	//std::cout << (*m_Window)->getMouseButton() << std::endl;
	return mouseHeld;
}

void Grid::setCursor(int value)
{
	if (m_CursorPos[0] + m_CursorPos[1] + m_CursorPos[2] != 3)
	{
		m_Grid[25 + m_CursorPos[0]][25 + m_CursorPos[1]][25 + m_CursorPos[2]] = value;
	}
	std::cout << m_CursorPos[0] <<","<< m_CursorPos[1] <<","<< m_CursorPos[2] << "        "<< m_Grid[25 + m_CursorPos[0]][25 + m_CursorPos[1]][25 + m_CursorPos[2]]<< std::endl;
}

void Grid::randomizeGrid(int boardRadius)
{
	srand(time(NULL));
	m_RiverDirection = (rand() % 6)+1;
	rollRivers(boardRadius);
	int roll = 0;

	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						//forest
						roll = rand() % 6;
						if (roll < 3) { m_GridLayer2[25 + i][25 + j][25 + k] = 27; }
						else if (roll == 5) { m_GridLayer2[25 + i][25 + j][25 + k] = 29; }
						else { m_GridLayer2[25 + i][25 + j][25 + k] = 28; }
					}

					if (rand() % 10 == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						//lake
						roll = rand() % 6;
						if (roll < 3) { m_GridLayer2[25 + i][25 + j][25 + k] = 33; }
						else if (roll == 5) { m_GridLayer2[25 + i][25 + j][25 + k] = 35; }
						else { m_GridLayer2[25 + i][25 + j][25 + k] = 34; }
					}
					
				}
			}
		}
	}

	expandGrid(boardRadius);
	cleanGrid(boardRadius);
}

void Grid::rollRivers(int boardRadius)
{
	srand(time(NULL));
	int roll = 0;

	//if N->S 1
	if (m_RiverDirection == 1) {
		int j = -boardRadius;
		for (int i = 0; i <= boardRadius; i++)
		{
			for (int k = boardRadius; k >= 0; k--)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						m_GridLayer1[25 + i][25 + j][25 + k] = 1;
					}
				}
			}
		}

		//N->S Loop
		for (int j = -boardRadius; j <= boardRadius - 1; j++)
		{
			for (int i = -boardRadius; i <= boardRadius; i++)
			{
				for (int k = -boardRadius; k <= boardRadius; k++)
				{
					if (i + j + k == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						roll = rand() % 20;
						if (roll <= 9)
						{
							m_GridLayer1[25 + i - 1][25 + j + 1][25 + k] = 1;
						}
						else if (roll >= 11)
						{
							m_GridLayer1[25 + i][25 + j + 1][25 + k - 1] = 1;
						}
						else
						{
							m_GridLayer1[25 + i - 1][25 + j + 1][25 + k] = 1;
							m_GridLayer1[25 + i][25 + j + 1][25 + k - 1] = 1;
						}
					}
				}
			}
		}
	}

	//if NW->SE 2
	if (m_RiverDirection == 2) {
		int i = boardRadius;
		for (int j = -boardRadius; j <= 0; j++)
		{
			for (int k = 0; k >= -boardRadius; k--)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						m_GridLayer1[25 + i][25 + j][25 + k] = 1;
					}
				}
			}
		}

		//NW->SE Loop
		for (int i = boardRadius; i >= -boardRadius+1; i--)
		{
			for (int j = -boardRadius; j <= boardRadius; j++)
			{
				for (int k = -boardRadius; k <= boardRadius; k++)
				{
					if (i + j + k == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						roll = rand() % 20;
						if (roll <= 9)
						{
							m_GridLayer1[25 + i - 1][25 + j][25 + k+1] = 1;
						}
						else if (roll >= 11)
						{
							m_GridLayer1[25 + i-1][25 + j + 1][25 + k ] = 1;
						}
						else
						{
							m_GridLayer1[25 + i - 1][25 + j][25 + k + 1] = 1;
							m_GridLayer1[25 + i - 1][25 + j + 1][25 + k] = 1;
						}
					}
				}
			}
		}
	}

	//if SW->NE 3
	if (m_RiverDirection == 3) {
		int k = -boardRadius;
		for (int j = 0; j <= boardRadius; j++)
		{
			for (int i = boardRadius; i >= 0; i--)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						m_GridLayer1[25 + i][25 + j][25 + k] = 1;
					}
				}
			}
		}

		//NW->SE Loop
		for (int k = -boardRadius; k <= boardRadius - 1; k++)
		{
			for (int j = -boardRadius; j <= boardRadius; j++)
			{
				for (int i = -boardRadius; i <= boardRadius; i++)
				{
					if (i + j + k == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						roll = rand() % 20;
						if (roll <= 9)
						{
							m_GridLayer1[25 + i][25 + j-1][25 + k + 1] = 1;
						}
						else if (roll >= 11)
						{
							m_GridLayer1[25 + i - 1][25 + j][25 + k+1] = 1;
						}
						else
						{
							m_GridLayer1[25 + i][25 + j - 1][25 + k + 1] = 1;
							m_GridLayer1[25 + i - 1][25 + j][25 + k + 1] = 1;
						}
					}
				}
			}
		}
	}

	//if S->N 4
	if (m_RiverDirection == 4) {
		int j = boardRadius;
		for (int i = 0; i >= -boardRadius; i--)
		{
			for (int k = -boardRadius; k <= 0; k++)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						m_GridLayer1[25 + i][25 + j][25 + k] = 1;
					}
				}
			}
		}

		//S->N Loop
		for (int j = boardRadius; j >= -boardRadius+1; j--)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				for (int i = -boardRadius; i <= boardRadius; i++)
				{
					if (i + j + k == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						roll = rand() % 20;
						if (roll <= 9)
						{
							m_GridLayer1[25 + i+1][25 + j - 1][25 + k] = 1;
						}
						else if (roll >= 11)
						{
							m_GridLayer1[25 + i][25 + j-1][25 + k + 1] = 1;
						}
						else
						{
							m_GridLayer1[25 + i + 1][25 + j - 1][25 + k] = 1;
							m_GridLayer1[25 + i][25 + j - 1][25 + k + 1] = 1;
						}
					}
				}
			}
		}
	}

	//if SW->NE 5
	if (m_RiverDirection == 5) {
		int i = -boardRadius;
		for (int j = boardRadius; j >= 0; j--)
		{
			for (int k = 0; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						m_GridLayer1[25 + i][25 + j][25 + k] = 1;
					}
				}
			}
		}

		//SW->NE Loop
		for (int i = -boardRadius; i <= boardRadius-1; i++)
		{
			for (int j = -boardRadius; j <= boardRadius; j++)
			{
				for (int k = -boardRadius; k <= boardRadius; k++)
				{
					if (i + j + k == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						roll = rand() % 20;
						if (roll <= 9)
						{
							m_GridLayer1[25 + i + 1][25 + j][25 + k-1] = 1;
						}
						else if (roll >= 11)
						{
							m_GridLayer1[25 + i+1][25 + j - 1][25 + k] = 1;
						}
						else
						{
							m_GridLayer1[25 + i + 1][25 + j][25 + k - 1] = 1;
							m_GridLayer1[25 + i + 1][25 + j - 1][25 + k] = 1;
						}
					}
				}
			}
		}
	}

	//if NW->SE 6
	if (m_RiverDirection == 6) {
		int k = boardRadius;
		for (int j = 0; j >= -boardRadius; j--)
		{
			for (int i = -boardRadius; i <= 0; i++)
			{
				if (i + j + k == 0)
				{
					if (rand() % 10 == 0)
					{
						m_GridLayer1[25 + i][25 + j][25 + k] = 1;
					}
				}
			}
		}

		//NW->SE Loop
		for (int k = boardRadius; k >= -boardRadius-1; k--)
		{
			for (int i = -boardRadius; i <= boardRadius; i++)
			{
				for (int j = -boardRadius; j <= boardRadius; j++)
				{
					if (i + j + k == 0 && m_GridLayer1[25 + i][25 + j][25 + k] == 1)
					{
						roll = rand() % 20;
						if (roll <= 9)
						{
							m_GridLayer1[25 + i + 1][25 + j][25 + k - 1] = 1;
						}
						else if (roll >= 11)
						{
							m_GridLayer1[25 + i][25 + j + 1][25 + k-1] = 1;
						}
						else
						{
							m_GridLayer1[25 + i + 1][25 + j][25 + k - 1] = 1;
							m_GridLayer1[25 + i][25 + j + 1][25 + k - 1] = 1;
						}
					}
				}
			}
		}
	}
}

void Grid::expandGrid(int boardRadius)
{
	//Lakes will need to work slightly seperate since they cannot have sudden changes of depthe like forest or rock.

	std::vector<int> tierone = {27,33};
	std::vector<int> tiertwo = {28,34};
	std::vector<int> tierthr = { 29,35 };
	//expand tier three
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					//Dense Lake
					if (m_GridLayer2[25 + i][25 + j][25 + k] == 35)
					{
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j - 1][25 + k]) == tierthr.end())
						{
							m_GridLayer2[25 + i + 1][25 + j - 1][25 + k] = 34;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j][25 + k - 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i + 1][25 + j][25 + k - 1] = 34;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j + 1][25 + k - 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i][25 + j + 1][25 + k - 1] = 34;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j + 1][25 + k]) == tierthr.end())
						{
							m_GridLayer2[25 + i - 1][25 + j + 1][25 + k] = 34;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j][25 + k + 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i - 1][25 + j][25 + k + 1] = 34;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j - 1][25 + k + 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i][25 + j - 1][25 + k + 1] = 34;
						}
					}
					//Dense Forest
					if (m_GridLayer2[25 + i][25 + j][25 + k] == 29)
					{
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j - 1][25 + k]) == tierthr.end())
						{
							m_GridLayer2[25 + i + 1][25 + j - 1][25 + k] = 28;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j][25 + k - 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i + 1][25 + j][25 + k - 1] = 28;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j + 1][25 + k - 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i][25 + j + 1][25 + k - 1] = 28;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j + 1][25 + k]) == tierthr.end())
						{
							m_GridLayer2[25 + i - 1][25 + j + 1][25 + k] = 28;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j][25 + k + 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i - 1][25 + j][25 + k + 1] = 28;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j - 1][25 + k + 1]) == tierthr.end())
						{
							m_GridLayer2[25 + i][25 + j - 1][25 + k + 1] = 28;
						}
					}
				}
			}
		}
	}

	//expand tier two
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					//Lake
					if (m_GridLayer2[25 + i][25 + j][25 + k] == 34)
					{
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j - 1][25 + k]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i + 1][25 + j - 1][25 + k]) == tiertwo.end())
						{
							m_GridLayer2[25 + i + 1][25 + j - 1][25 + k] = 33;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j][25 + k - 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i + 1][25 + j][25 + k - 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i + 1][25 + j][25 + k - 1] = 33;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j + 1][25 + k - 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i][25 + j + 1][25 + k - 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i][25 + j + 1][25 + k - 1] = 33;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j + 1][25 + k]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i - 1][25 + j + 1][25 + k]) == tiertwo.end())
						{
							m_GridLayer2[25 + i - 1][25 + j + 1][25 + k] = 33;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j][25 + k + 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i - 1][25 + j][25 + k + 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i - 1][25 + j][25 + k + 1] = 33;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j - 1][25 + k + 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i][25 + j - 1][25 + k + 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i][25 + j - 1][25 + k + 1] = 33;
						}
					}
					//Forest
					if (m_GridLayer2[25 + i][25 + j][25 + k] == 28)
					{
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j - 1][25 + k]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i + 1][25 + j - 1][25 + k]) == tiertwo.end())
						{
							m_GridLayer2[25 + i + 1][25 + j - 1][25 + k] = 27;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i + 1][25 + j][25 + k - 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i + 1][25 + j][25 + k - 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i + 1][25 + j][25 + k - 1] = 27;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j + 1][25 + k - 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i][25 + j + 1][25 + k - 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i][25 + j + 1][25 + k - 1] = 27;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j + 1][25 + k]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i - 1][25 + j + 1][25 + k]) == tiertwo.end())
						{
							m_GridLayer2[25 + i - 1][25 + j + 1][25 + k] = 27;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i - 1][25 + j][25 + k + 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i - 1][25 + j][25 + k + 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i - 1][25 + j][25 + k + 1] = 27;
						}
						if (std::find(tierthr.begin(), tierthr.end(), m_GridLayer2[25 + i][25 + j - 1][25 + k + 1]) == tierthr.end() && std::find(tiertwo.begin(), tiertwo.end(), m_GridLayer2[25 + i][25 + j - 1][25 + k + 1]) == tiertwo.end())
						{
							m_GridLayer2[25 + i][25 + j - 1][25 + k + 1] = 27;
						}
					}
				}
			}
		}
	}
}

void Grid::cleanGrid(int boardRadius)
{
	srand(time(NULL));
	std::vector<int> tierone = { 27,33 };
	std::vector<int> tiertwo = { 28,34 };
	std::vector<int> tierthr = { 29,35 };
	int roll = 0;
	Uint8 compare;
	//remove tier one
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					if (std::find(tierone.begin(), tierone.end(), m_GridLayer2[i + 25][j + 25][k + 25]) != tierone.end())
					{
						roll = rand() % 6;
						if (roll == 0) { m_GridLayer2[i + 25][j + 25][k + 25] = 0; }
					}
				}
			}
		}
	}

	//reduce tier two
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					//forest
					if (m_GridLayer2[i + 25][j + 25][k + 25] == 28)
					{
						compare = m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 27, 28, 29);
						if (compare != 0x3F) { m_GridLayer2[i + 25][j + 25][k + 25] = 27; }
					}
					//lake
					if (m_GridLayer2[i + 25][j + 25][k + 25] == 34)
					{
						compare=m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 33,34,35);
						if (compare != 0x3F) { m_GridLayer2[i + 25][j + 25][k + 25] = 33; }
					}
				}
			}
		}
	}

	//reduce tier three
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					//forest
					if (m_GridLayer2[i + 25][j + 25][k + 25] == 29)
					{
						compare = m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 999, 28, 29);
						if (compare != 0x3F) { m_GridLayer2[i + 25][j + 25][k + 25] = 28; }
					}
					//lake
					if (m_GridLayer2[i + 25][j + 25][k + 25] == 35)
					{
						compare = m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 999, 34, 35);
						if (compare != 0x3F) { m_GridLayer2[i + 25][j + 25][k + 25] = 34; }
					}
				}
			}
		}
	}

	//reduce tier two second wave
	for (int i = -boardRadius; i <= boardRadius; i++)
	{
		for (int j = -boardRadius; j <= boardRadius; j++)
		{
			for (int k = -boardRadius; k <= boardRadius; k++)
			{
				if (i + j + k == 0)
				{
					//forest
					if (m_GridLayer2[i + 25][j + 25][k + 25] == 28)
					{
						compare = m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 27, 28, 29);
						if (compare != 0x3F) { m_GridLayer2[i + 25][j + 25][k + 25] = 27; }
					}
					//lake
					if (m_GridLayer2[i + 25][j + 25][k + 25] == 34)
					{
						compare = m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 33, 34, 35);
						if (compare != 0x3F) { m_GridLayer2[i + 25][j + 25][k + 25] = 33; }
					}
				}
			}
		}
	}
}

void Grid::chooseRiver(int i,int j,int k,int xPos,int yPos)
{
	Uint8 surroundingTiles = m_Maths->compareAdjacentHex(m_GridLayer1, i, j, k, 1, 999, 999);

	//remove perpendicular flow
	if (m_RiverDirection == 1 || m_RiverDirection == 4) { surroundingTiles = surroundingTiles & 0xFD; surroundingTiles = surroundingTiles & 0xEF; }
	if (m_RiverDirection == 2 || m_RiverDirection == 5) { surroundingTiles = surroundingTiles & 0xDF; surroundingTiles = surroundingTiles & 0xFB; }
	if (m_RiverDirection == 3 || m_RiverDirection == 6) { surroundingTiles = surroundingTiles & 0xFE; surroundingTiles = surroundingTiles & 0xF7; }

	switch (surroundingTiles) {
		//Using Sprite 30
	case 0x09:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[30], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x12:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[30], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x24:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[30], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 31
	case 0x11:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[31], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x22:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[31], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x05:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[31], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x0A:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[31], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;
	case 0x14:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[31], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x28:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[31], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 32
	case 0x18:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[32], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x30:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[32], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x21:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[32], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x03:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[32], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x06:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[32], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x0C:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[32], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 33
	case 0x16:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[33], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x2C:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[33], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x19:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[33], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x32:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[33], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x25:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[33], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x0B:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[33], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 34
	case 0x1A:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[34], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x34:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[34], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x29:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[34], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x13:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[34], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x26:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[34], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x0D:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[34], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 35
	case 0x15:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[35], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x2A:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[35], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 36
	case 0x1C:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[36], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x38:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[36], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x31:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[36], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x23:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[36], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x07:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[36], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x0E:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[36], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 37
	case 0x17:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[37], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x2E:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[37], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x1D:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[37], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x3A:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[37], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x35:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[37], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x2B:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[37], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 38
	case 0x1E:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[38], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x3C:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[38], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x39:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[38], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x33:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[38], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x27:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[38], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x0F:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[38], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 39
	case 0x36:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[39], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x2D:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[39], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x1B:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[39], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 40
	case 0x1F:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[40], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	case 0x3E:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[40], m_ViewPort, 60, NULL, SDL_FLIP_NONE);
		break;
	case 0x3D:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[40], m_ViewPort, 120, NULL, SDL_FLIP_NONE);
		break;
	case 0x3B:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[40], m_ViewPort, 180, NULL, SDL_FLIP_NONE);
		break;
	case 0x37:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[40], m_ViewPort, 240, NULL, SDL_FLIP_NONE);
		break;
	case 0x2F:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[40], m_ViewPort, 300, NULL, SDL_FLIP_NONE);
		break;

		//using sprite 41
	case 0x3F:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[41], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;

		//throw error sprite
	default:
		m_Renderer->render(xPos, yPos, m_Renderable->getRenderable(), &m_sprite[6], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
		break;
	}
}

void Grid::chooseCoast(int i, int j, int k, int x, int y)
{
	Uint8 surroundingTiles = m_Maths->compareAdjacentHex(m_GridLayer2, i, j, k, 33, 34, 999);
	switch (surroundingTiles) {

	//Using Sprite 50
	case 0x3F:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[50], m_ViewPort, 0, NULL, SDL_FLIP_NONE);break;
	case 0x00:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[50], m_ViewPort, 0, NULL, SDL_FLIP_NONE);break;

	//using sprite 51
	case 0x01:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[51], m_ViewPort, 120, NULL, SDL_FLIP_NONE);break;
	case 0x02:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[51], m_ViewPort, 180, NULL, SDL_FLIP_NONE);break;
	case 0x04:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[51], m_ViewPort, 240, NULL, SDL_FLIP_NONE);break;
	case 0x08:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[51], m_ViewPort, 300, NULL, SDL_FLIP_NONE);break;
	case 0x10:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[51], m_ViewPort, 0, NULL, SDL_FLIP_NONE);break;
	case 0x20:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[51], m_ViewPort, 60, NULL, SDL_FLIP_NONE);break;

	//using sprite 52
	case 0x03:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[52], m_ViewPort, 120, NULL, SDL_FLIP_NONE);break;
	case 0x06:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[52], m_ViewPort, 180, NULL, SDL_FLIP_NONE);break;
	case 0x0C:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[52], m_ViewPort, 240, NULL, SDL_FLIP_NONE);break;
	case 0x18:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[52], m_ViewPort, 300, NULL, SDL_FLIP_NONE);break;
	case 0x30:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[52], m_ViewPort, 0, NULL, SDL_FLIP_NONE);break;
	case 0x21:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[52], m_ViewPort, 60, NULL, SDL_FLIP_NONE);break;

	//using sprite 53
	case 0x07:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[53], m_ViewPort, 120, NULL, SDL_FLIP_NONE);break;
	case 0x0E:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[53], m_ViewPort, 180, NULL, SDL_FLIP_NONE);break;
	case 0x1C:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[53], m_ViewPort, 240, NULL, SDL_FLIP_NONE);break;
	case 0x38:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[53], m_ViewPort, 300, NULL, SDL_FLIP_NONE);break;
	case 0x31:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[53], m_ViewPort, 0, NULL, SDL_FLIP_NONE);break;
	case 0x23:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[53], m_ViewPort, 60, NULL, SDL_FLIP_NONE);break;

	//using sprite 54
	case 0x0F:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[54], m_ViewPort, 120, NULL, SDL_FLIP_NONE);break;
	case 0x1E:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[54], m_ViewPort, 180, NULL, SDL_FLIP_NONE);break;
	case 0x3C:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[54], m_ViewPort, 240, NULL, SDL_FLIP_NONE);break;
	case 0x39:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[54], m_ViewPort, 300, NULL, SDL_FLIP_NONE);break;
	case 0x33:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[54], m_ViewPort, 0, NULL, SDL_FLIP_NONE);break;
	case 0x27:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[54], m_ViewPort, 60, NULL, SDL_FLIP_NONE);break;

	//using sprite 55
	case 0x1F:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[55], m_ViewPort, 120, NULL, SDL_FLIP_NONE); break;
	case 0x3E:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[55], m_ViewPort, 180, NULL, SDL_FLIP_NONE); break;
	case 0x3D:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[55], m_ViewPort, 240, NULL, SDL_FLIP_NONE); break;
	case 0x3B:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[55], m_ViewPort, 300, NULL, SDL_FLIP_NONE); break;
	case 0x37:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[55], m_ViewPort, 0, NULL, SDL_FLIP_NONE); break;
	case 0x2F:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[55], m_ViewPort, 60, NULL, SDL_FLIP_NONE); break;

	//using sprite 56
	case 0x12:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[56], m_ViewPort, 0, NULL, SDL_FLIP_NONE); break;
	case 0x24:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[56], m_ViewPort, 60, NULL, SDL_FLIP_NONE); break;
	case 0x09:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[56], m_ViewPort, 120, NULL, SDL_FLIP_NONE); break;

	//using sprite 57
	case 0x14:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[57], m_ViewPort, 0, NULL, SDL_FLIP_NONE); break;
	case 0x28:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[57], m_ViewPort, 60, NULL, SDL_FLIP_NONE); break;
	case 0x11:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[57], m_ViewPort, 120, NULL, SDL_FLIP_NONE); break;
	case 0x22:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[57], m_ViewPort, 180, NULL, SDL_FLIP_NONE); break;
	case 0x05:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[57], m_ViewPort, 240, NULL, SDL_FLIP_NONE); break;
	case 0x0A:m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[57], m_ViewPort, 300, NULL, SDL_FLIP_NONE); break;


	//throw error
	default:
		m_Renderer->render(x, y, m_Renderable->getRenderable(), &m_sprite[6], m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	}
}

int Grid::gridEffect(int i, int j, int k, int step)
{
	/*
	The object grid can occupy numbers 26-98.
	0 is reserved for blank spaces (likely unused in the future except as an error stand in)
	1-25 Are reserved for pathfinding.
	99+ is reserved for the cursor and pathfinding.
	26-30 is reserved a generic debugs.

	This is prone to change.

	Although there is no overlap with the sub 25 values and the object grid they are seperated for safety purposes.
	*/

	switch (m_GridLayer2[i][j][k]) 
	{
	case 27:
		step -= 1;
		break;
	case 28:
		step -= 2;
		break;
	case 29:
		step -= 3;
		break;
	case 30:
		step = 0;
		break;

	}
	return step;
}

void Grid::findPath()
{
	//Consider making a seperate grid...may be too much and its also possible that the two existing grids should be merged.

	int currentPosi = 25 + m_CursorPos[0];
	int currentPosj = 25 + m_CursorPos[1];
	int currentPosk = 25 + m_CursorPos[2];
	
	//m_Grid[25 + m_CursorPos[0]][25 + m_CursorPos[1]][25 + m_CursorPos[2]];
	int i=25;
	while(i>0)
	{
		if (m_Grid[currentPosi + 1][currentPosj - 1][currentPosk] == i) 
		{ 
			currentPosi+=1;
			currentPosj-=1;
			m_Grid[currentPosi][currentPosj][currentPosk] = i + 99;
			m_OverlayGrid[currentPosi][currentPosj][currentPosk] = 2;
			if (i == 25)
			{
				break;
			}
			else
			{
				i = 25;
			}

		}
		else if (m_Grid[currentPosi + 1][currentPosj][currentPosk - 1] == i)
		{
			currentPosi++;
			currentPosk--;
			m_Grid[currentPosi][currentPosj][currentPosk] = i + 99;
			m_OverlayGrid[currentPosi][currentPosj][currentPosk] = 2;
			if (i == 25)
			{
				break;
			}
			else
			{
				i = 25;
			}
		}
		else if (m_Grid[currentPosi][currentPosj + 1][currentPosk - 1] == i)
		{
			currentPosj++;
			currentPosk--;
			m_Grid[currentPosi][currentPosj][currentPosk] = i + 99;
			m_OverlayGrid[currentPosi][currentPosj][currentPosk] = 2;
			if (i == 25)
			{
				break;
			}
			else
			{
				i = 25;
			}
		}
		else if (m_Grid[currentPosi - 1][currentPosj + 1][currentPosk] == i)
		{
			currentPosj++;
			currentPosi--;
			m_Grid[currentPosi][currentPosj][currentPosk] = i + 99;
			m_OverlayGrid[currentPosi][currentPosj][currentPosk] = 2;
			if (i == 25)
			{
				break;
			}
			else
			{
				i = 25;
			}
		}
		else if (m_Grid[currentPosi - 1][currentPosj][currentPosk + 1] == i)
		{ 
			currentPosk++;
			currentPosi--;
			m_Grid[currentPosi][currentPosj][currentPosk] = i + 99;
			m_OverlayGrid[currentPosi][currentPosj][currentPosk] = 2;
			if (i == 25)
			{
				break;
			}
			else
			{
				i = 25;
			}
		}
		else if (m_Grid[currentPosi][currentPosj - 1][currentPosk + 1] == i)
		{
			currentPosk++;
			currentPosj--;
			m_Grid[currentPosi][currentPosj][currentPosk] = i + 99;
			m_OverlayGrid[currentPosi][currentPosj][currentPosk] = 2;
			if (i == 25)
			{
				break;
			}
			else
			{
				i = 25;
			}
		}
		else
		{
			i--;
		}
		
	}
	//std::cout << m_Grid[25 + m_CursorPos[0] + 1][25 + m_CursorPos[1] - 1][25 + m_CursorPos[2]] << std::endl;
}

int Grid::getRiverDirection()
{
	return (m_RiverDirection*60)+210;
}
