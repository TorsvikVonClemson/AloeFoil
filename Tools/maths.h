#pragma once

#include <stdio.h>
#include <math.h>

#include "..\Graphics\Window\window.h"

#define PI 3.14159265

class Maths
{
public:
	Maths();
	~Maths();
	double sinWave(double offsetMin, double offsetMax,double offsetCurrent);
	bool findRect(Window* window, int xMin, int xMax, int yMin, int yMax);
	Uint8 compareAdjacentHex(int hexGrid[][50][50], int i, int j, int k, int find1, int find2,int find3);

};