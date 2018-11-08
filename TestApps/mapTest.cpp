#include "mapTest.h"

MapTest::MapTest(int width, int height)
{

	m_ScreenX = width;
	m_ScreenY = height;

	emptyFailMat();

	//define sprite sheet
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_sprite[i + j * 10].x = 16 * i;
			m_sprite[i + j * 10].y = 16 * j;
			m_sprite[i + j * 10].w = 16;
			m_sprite[i + j * 10].h = 16;
		}
	}


	m_TilesX= (m_ScreenX / m_sprite[0].w);
	m_TilesY = (m_ScreenY / m_sprite[0].h);

	//Fill a sprite matrix with plains tiles (40)
	for (int i = 0; i < m_TilesX; i++)
	{
		for (int j = 0; j < m_TilesY; j++)
		{
			m_matrix[i + j * m_TilesX] = 40;
		}
	}

	northSouthRiver();

	//place forests
	elementFill(m_matrix, m_matrix, 40, 0, 1, 2);

	//place stone
	//elementFill(m_matrix, m_matrix, 40, 10, 11, 12);


}

void MapTest::run(Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	//background loop
	for (int i = 0; i < m_TilesX; i++)
	{
		for (int j = 0; j < m_TilesY; j++)
		{
			renderer->render(m_sprite[m_matrix[i + j * m_TilesX]].w*i, m_sprite[m_matrix[i + j * m_TilesX]].h*j, renderable->getRenderable(), &m_sprite[m_matrix[i + j * m_TilesX]], viewport, 0, NULL, flip);
		}
	}
	//river layer loop
	for (int i = 0; i < m_TilesX; i++)
	{
		for (int j = 0; j < m_TilesY; j++)
		{
			if (m_RiverMatrix[i + j * m_TilesX] != 0)
			{
				renderer->render(m_sprite[m_RiverMatrix[i + j * m_TilesX]].w*i, m_sprite[m_RiverMatrix[i + j * m_TilesX]].h*j, renderable->getRenderable(), &m_sprite[m_RiverMatrix[i + j * m_TilesX]], viewport, 0, NULL, flip);
			}
		}
	}

	renderer->display();
}

void MapTest::northSouthRiver()
{
	int direction;
	int roll;

	//Randomly place river base along the top
	for (int i = 0; i < m_TilesX; i++)
	{
		if (rand() % 10 == 0)
		{
			m_RiverMatrix[i] = 30;
		}
	}

	//Extend Rivers Southward

	for (int j = 0; j+1 < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * m_TilesX] == 30 || m_RiverMatrix[i + j * m_TilesX] == 33 || m_RiverMatrix[i + j * m_TilesX] == 35)
			{
				direction = rand() % 3;

				if (direction == 0 && i>0)	//SouthWest
				{
					m_RiverMatrix[i + (j + 1) * m_TilesX] = 32;
					m_RiverMatrix[(i - 1) + (j + 1) * m_TilesX] = 33;
				}
				else if (direction == 1)	//South
				{
					m_RiverMatrix[i + (j + 1) * m_TilesX] = 30;
				}
				else if (direction == 2 && i < m_TilesX)	//SouthEast
				{
					m_RiverMatrix[i + (j + 1) * m_TilesX] = 31;
					m_RiverMatrix[(i + 1) + (j + 1) * m_TilesX] = 35;
				}
				else
				{
					m_RiverMatrix[i + (j + 1) * m_TilesX] = 30;
				}
			}
		}
	}

	//Make Lakes on river tiles
	for (int j = 0; j < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * 40] != 0)
			{
				roll = rand() % 10;
				if (roll == 0)
				{
					roll = rand() % 10;
					if (roll > 5)
					{
						m_RiverMatrix[i + j * 40] = 20;
					}
					if (roll < 9 && roll > 4)
					{
						m_RiverMatrix[i + j * 40] = 21;
					}
					if (roll == 9)
					{
						m_RiverMatrix[i + j * 40] = 22;
					}
				}
			}
		}
	}

	//Expand Lake Tiles Deep
	m_FailVals[0] = 22;
	for (int j = 0; j < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * 40] == 22)
			{
				perimeterFill(i, j, m_RiverMatrix, m_RiverMatrix, 21);
			}
		}
	}
	emptyFailMat();

	//Expand Lake Tiles Med
	m_FailVals[0] = 21;
	m_FailVals[1] = 22;
	for (int j = 0; j < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * m_TilesX] == 21)
			{
				perimeterFill(i, j, m_RiverMatrix, m_RiverMatrix, 20);
			}
		}
	}
	emptyFailMat();


	//Delete Shallow Lake tiles

	for (int j = 0; j < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * 40] == 20)
			{
				roll = rand() % 6;
				if (roll == 0)
				{
					m_RiverMatrix[i + j * 40] = 0;
				}
			}
		}
	}

	//Convert Medium Lake tiles

	for (int j = 0; j< m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * 40] == 21)
			{
				perimeterCheck(i, j, m_RiverMatrix, m_RiverMatrix, 20, 0);
			}

		}
	}

	//Convert Deep Lake tiles

	for (int j = 0; j< m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (m_RiverMatrix[i + j * 40] == 22)
			{
				perimeterCheck(i, j, m_RiverMatrix, m_RiverMatrix, 21, 20);
			}

		}
	}


}

void MapTest::perimeterFill(int X, int Y, int * matrixAffected, int * matrixChecked, int newVal)
{
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X - 1) + (Y - 1) * m_TilesX]) == std::end(m_FailVals) && Y!= 0 && X!= 0) { matrixAffected[(X- 1) + (Y- 1) * m_TilesX] = newVal; }
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X - 0) + (Y - 1) * m_TilesX]) == std::end(m_FailVals)&& Y!= 0) { matrixAffected[(X- 0) + (Y- 1) * m_TilesX] = newVal; }
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X + 1) + (Y - 1) * m_TilesX]) == std::end(m_FailVals)&& Y!= 0 && X!= m_TilesX) { matrixAffected[(X+ 1) + (Y- 1) * m_TilesX] = newVal; }
			 																								 
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X - 1) + (Y - 0) * m_TilesX]) == std::end(m_FailVals) && X!= 0) { matrixAffected[(X- 1) + (Y) * m_TilesX] = newVal; }
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X - 0) + (Y - 0) * m_TilesX]) == std::end(m_FailVals)) { matrixAffected[(X- 0) + (Y) * m_TilesX] = newVal; }
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X + 1) + (Y - 0) * m_TilesX]) == std::end(m_FailVals)&& X!= m_TilesX) { matrixAffected[(X+ 1) + (Y) * m_TilesX] = newVal; }
			 																								 
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X - 1) + (Y + 1) * m_TilesX]) == std::end(m_FailVals) && Y!= m_ScreenY / m_sprite[0].h&& X!= 0) { matrixAffected[(X- 1) + (Y+ 1) * m_TilesX] = newVal; }
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X - 0) + (Y + 1) * m_TilesX]) == std::end(m_FailVals) && Y!= m_ScreenY / m_sprite[0].h) { matrixAffected[(X- 0) + (Y+ 1) * m_TilesX] = newVal; }
	if (std::find(std::begin(m_FailVals), std::end(m_FailVals), matrixChecked[(X + 1) + (Y + 1) * m_TilesX]) == std::end(m_FailVals) && Y!= m_ScreenY / m_sprite[0].h&& X!= m_TilesX) { matrixAffected[(X+ 1) + (Y+ 1) * m_TilesX] = newVal; }
}

void MapTest::elementFill(int * matrixAffected, int * matrixChecked, int valid, int low, int med, int high)
{
	int roll;

	//Place base tiles
	for (int j = 0; j < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (matrixChecked[i + j * m_TilesX] == valid)
			{
				roll = rand() % 20;
				if (roll == 0)
				{
					roll = rand() % 10;
					if (roll > 5)
					{
						matrixChecked[i + j * m_TilesX] = low;
					}
					if (roll < 9 && roll > 4)
					{
						matrixChecked[i + j * m_TilesX] = med;
					}
					if (roll == 9)
					{
						matrixChecked[i + j * m_TilesX] = high;
					}
				}
			}
		}
	}
	//Expand Tiles High
	m_FailVals[0] = high;
	for (int j = 0; j <  m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (matrixAffected[i + j * m_TilesX] == high)
			{
				perimeterFill(i, j, matrixAffected, matrixAffected, med);
			}
		}
	}
	emptyFailMat();

	//Expand  Tiles Med
	m_FailVals[0] = med;
	m_FailVals[1] = high;
	for (int j = 0; j <  m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (matrixAffected[i + j * m_TilesX] == med)
			{
				perimeterFill(i, j, matrixAffected, matrixAffected, low);
			}
		}
	}
	emptyFailMat();

	//Delete Low
	for (int j = 0; j < m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (matrixAffected[i + j * m_TilesX] == low)
			{
				roll = rand() % 6;
				if (roll == 0)
				{
					matrixAffected[i + j * m_TilesX] = 40;
				}
			}
		}
	}

	//Update Med
	for (int j = 0; j< m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (matrixAffected[i + j * m_TilesX] == med)
			{
				perimeterCheck(i, j, matrixAffected, matrixAffected, low, valid);
			}

		}
	}

	//Update high
	for (int j = 0; j< m_TilesY; j++)
	{
		for (int i = 0; i < m_TilesX; i++)
		{
			if (matrixAffected[i + j * m_TilesX] == high)
			{
				perimeterCheck(i, j, matrixAffected, matrixAffected, med, low);
			}

		}
	}
}

void MapTest::perimeterCheck(int X, int Y, int* matrixAffected, int* matrixChecked, int newVal, int failVal)
{
	if (matrixChecked[(X- 1) + (Y- 1) * m_TilesX] == failVal && X!=0 && Y!=0) { matrixAffected[X+ Y* m_TilesX] = newVal; }
	if (matrixChecked[X+ (Y- 1) * m_TilesX] == failVal && Y!=0) { matrixAffected[X+ Y* m_TilesX] = newVal; }
	if (matrixChecked[(X+ 1) + (Y- 1) * m_TilesX] == failVal && X!=m_TilesX && Y!=0) { matrixAffected[X+ Y* m_TilesX] = newVal; }

	if (matrixChecked[(X- 1) + Y* m_TilesX] == failVal && X!=0) { matrixAffected[X+ Y* m_TilesX] = newVal; }
	if (matrixChecked[X+ Y* m_TilesX] == failVal) { matrixAffected[X+ Y* m_TilesX] = newVal; }
	if (matrixChecked[(X+ 1) + Y* m_TilesX] == failVal && X!= m_TilesX) { matrixAffected[X+ Y* m_TilesX] = newVal; }

	if (matrixChecked[(X- 1) + (Y+ 1) * m_TilesX] == failVal && X!= 0 && Y!=m_TilesY) { matrixAffected[X+ Y* m_TilesX] = newVal; }
	if (matrixChecked[X+ (Y+ 1) * m_TilesX] == failVal && Y!=m_TilesY) { matrixAffected[X+ Y* m_TilesX] = newVal; }
	if (matrixChecked[(X+ 1) + (Y+ 1) * m_TilesX] == failVal&& X!=m_TilesX && Y!=m_TilesY) { matrixAffected[X+ Y*  m_TilesX] = newVal; }
}

void MapTest::emptyFailMat()
{
	for (int i = 0; i < 10; i++)
	{
		m_FailVals[i] = 666;
	}
}
