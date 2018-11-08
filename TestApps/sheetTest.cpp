#include "sheetTest.h"

SheetTest::SheetTest(int width, int height)
{
	srand(time(NULL));

	m_ScreenX = width;
	m_ScreenY = height;
	m_Rot = 0;


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

	//Randomly fill a sprite matrix with numbers 1-4
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			m_matrix[i + j * 10] = 10+rand() % 4;
		}
	}
}

void SheetTest::run(Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	////background loop
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	for (int i = 0; i <= m_ScreenX / m_sprite[0].w; i++)
	{
		for (int j = 0; j <= m_ScreenY / m_sprite[0].h; j++)
		{
			if (j == 15) { renderer->render(m_sprite[14].w*i, m_sprite[14].h*j, renderable->getRenderable(), &m_sprite[14], viewport,0,NULL,flip); }
			if (j < 15) { renderer->render(m_sprite[2].w*i, m_sprite[0].h*j, renderable->getRenderable(), &m_sprite[0], viewport,0, NULL, flip); }
		}
	}

	//background loop
	for (int i = 0; i <= m_ScreenX / m_sprite[0].w; i++)
	{
		for (int j = 16; j <= m_ScreenY / m_sprite[0].h; j++)
		{
			renderer->render(m_sprite[m_matrix[i + j * 30]].w*i, m_sprite[m_matrix[i + j * 30]].h*j, renderable->getRenderable(), &m_sprite[m_matrix[i + j * 30]], viewport, 0, NULL, flip);
			renderable->modulateColour(255 - (j - 14) * 16, 255 - (j - 14) * 16, 255 - (j - 14) * 16);
		}
	}
	renderer->display();
//foreground
	int i = 35;
	int j = 3;
	renderer->render(m_sprite[4].w*i, m_sprite[4].h*j, renderable->getRenderable(), &m_sprite[4], viewport, m_Rot, NULL, flip);
	renderer->display();

	m_Rot+=1;
}

