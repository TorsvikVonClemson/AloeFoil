#include "maths.h"

Maths::Maths()
{
}

Maths::~Maths()
{
}

double Maths::sinWave(double offsetMin, double offsetMax, double offsetCurrent)
{
	double degree =(360 * (offsetCurrent / (offsetMax - offsetMin)));
	double result= sin(degree*PI / 180);
	return result;
}

bool Maths::findRect(Window * window, int xMin, int xMax, int yMin, int yMax)
{
	if ((window->getMousePosX() > xMin) && (window->getMousePosX() < xMax) && (window->getMousePosY() > yMin) && (window->getMousePosY() < yMax))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Uint8 Maths::compareAdjacentHex(int hexGrid[][50][50], int i,int j,int k, int find1,int find2,int find3)
{
	//searches for 1 or 2 values
	//if there is only one parameter, set find2 to 999
	Uint8 result=0x00;

	if (hexGrid[25 + i + 1][25 + j - 1][25 + k] == find1) { result += 0x01; }
	if (hexGrid[25 + i + 1][25 + j][25 + k - 1] == find1) { result += 0x02; }
	if (hexGrid[25 + i][25 + j + 1][25 + k - 1] == find1) { result += 0x04; }
	if (hexGrid[25 + i - 1][25 + j + 1][25 + k] == find1) { result += 0x08; }
	if (hexGrid[25 + i - 1][25 + j][25 + k + 1] == find1) { result += 0x10; }
	if (hexGrid[25 + i][25 + j - 1][25 + k + 1] == find1) { result += 0x20; }

	if (hexGrid[25 + i + 1][25 + j - 1][25 + k] == find2) { result += 0x01; }
	if (hexGrid[25 + i + 1][25 + j][25 + k - 1] == find2) { result += 0x02; }
	if (hexGrid[25 + i][25 + j + 1][25 + k - 1] == find2) { result += 0x04; }
	if (hexGrid[25 + i - 1][25 + j + 1][25 + k] == find2) { result += 0x08; }
	if (hexGrid[25 + i - 1][25 + j][25 + k + 1] == find2) { result += 0x10; }
	if (hexGrid[25 + i][25 + j - 1][25 + k + 1] == find2) { result += 0x20; }

	if (hexGrid[25 + i + 1][25 + j - 1][25 + k] == find3) { result += 0x01; }
	if (hexGrid[25 + i + 1][25 + j][25 + k - 1] == find3) { result += 0x02; }
	if (hexGrid[25 + i][25 + j + 1][25 + k - 1] == find3) { result += 0x04; }
	if (hexGrid[25 + i - 1][25 + j + 1][25 + k] == find3) { result += 0x08; }
	if (hexGrid[25 + i - 1][25 + j][25 + k + 1] == find3) { result += 0x10; }
	if (hexGrid[25 + i][25 + j - 1][25 + k + 1] == find3) { result += 0x20; }

	return result;
}


