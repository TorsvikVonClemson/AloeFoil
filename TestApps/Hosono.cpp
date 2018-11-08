#include "Hosono.h"

Hosono::Hosono(int width, int height)
{
	srand(time(NULL));

	m_ScreenX = width;
	m_ScreenY = height;
	m_Rot = 0;
	m_PosX = 0;
	m_PosY = 0;
	m_AnimationTimer = 16;



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

	//Systematicly fill a sprite matrix with numbers 1-4
	for (int i = 0; i < 10; i=i+2)
	{
		for (int j = 0; j < 120; j++)
		{
			if (j % 2 == 0) 
			{ 
				m_matrix[i + j * 10] = 0; 
				m_matrix[i + j * 10] = 1;
			}
			else
			{
				m_matrix[i + j * 10] = 10;
				m_matrix[i + j * 10] = 11;
			}
		}
	}
}

void Hosono::run(Window* window, Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{

	m_Flip = SDL_FLIP_NONE;

	//possible state. If large enought another file
	if (m_InputTimer >= 9) { playfield(window); }


	//background loop
	for (int i = 0; i <= m_ScreenX / m_sprite[0].w; i++)
	{
		for (int j = 0; j <= m_ScreenY / m_sprite[0].h; j++)
		{
			renderer->render(m_sprite[m_matrix[i + j * 30]].w*i, m_sprite[m_matrix[i + j * 30]].h*j, renderable->getRenderable(), &m_sprite[m_matrix[i + j * 30]], viewport, 0, NULL, m_Flip);
		}
	}

	//foreground
	int i = 35;
	int j = 3;
	renderer->render(m_sprite[40].w*i, m_sprite[40].h*j, renderable->getRenderable(), &m_sprite[40], viewport, m_Rot, NULL, m_Flip);

	if (m_MoveState==1) { moveCursorUp(renderer,renderable, viewport); }
	if (m_MoveState == 2) { moveCursorUpRight(renderer, renderable, viewport); }
	if (m_MoveState==3) { moveCursorRight(renderer, renderable, viewport); }
	if (m_MoveState==4) { moveCursorDownRight(renderer, renderable, viewport); }
	if (m_MoveState==5) { moveCursorDown(renderer, renderable, viewport); }
	if (m_MoveState == 6) { moveCursorDownLeft(renderer, renderable, viewport); }
	if (m_MoveState == 7) { moveCursorLeft(renderer, renderable, viewport); }
	if (m_MoveState == 8) { moveCursorUpLeft(renderer, renderable, viewport); }
	if (m_MoveState==0)
	{
		renderer->render(m_sprite[20].w*m_PosX, m_sprite[20].h*m_PosY, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1), m_sprite[21].h*m_PosY, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX, m_sprite[30].h*(m_PosY + 1), renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1), m_sprite[31].h*(m_PosY + 1), renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
	}


	renderer->display();

	m_Rot += 3;
	m_InputTimer++;
}

void Hosono::playfield(Window* window)
{
	//state for controls while on the playfield

	m_KeyPressed=window->getKeyPressed();

	//Clockwise starting from 1 at 12

	if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosY -= 2; m_InputTimer = 0;  m_MoveState = 1;}
	if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosY -= 2; m_PosX += 2; m_InputTimer = 0;  m_MoveState = 2; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosX+=2;  m_InputTimer = 0; m_MoveState = 3;}
	if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosY += 2; m_PosX += 2;  m_InputTimer = 0; m_MoveState = 4; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && !m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosY+=2; m_InputTimer = 0; m_MoveState = 5;}
	if (!m_KeyPressed[SDL_SCANCODE_UP] && m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosY += 2; m_PosX -= 2; m_InputTimer = 0; m_MoveState = 6; }
	if (!m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosX-=2; m_InputTimer = 0; m_MoveState = 7;}
	if (m_KeyPressed[SDL_SCANCODE_UP] && !m_KeyPressed[SDL_SCANCODE_DOWN] && m_KeyPressed[SDL_SCANCODE_LEFT] && !m_KeyPressed[SDL_SCANCODE_RIGHT]) { m_PosY -= 2; m_PosX -= 2; m_InputTimer = 0; m_MoveState = 8; }
}

void Hosono::moveCursorUp(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX, m_sprite[20].h*m_PosY + m_AnimationTimer, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1), m_sprite[21].h*m_PosY + m_AnimationTimer, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX, m_sprite[30].h*(m_PosY + 1) + m_AnimationTimer, renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1), m_sprite[31].h*(m_PosY + 1) + m_AnimationTimer, renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer-=4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorUpLeft(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX + m_AnimationTimer, m_sprite[20].h*m_PosY + m_AnimationTimer, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1) + m_AnimationTimer, m_sprite[21].h*m_PosY + m_AnimationTimer, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX + m_AnimationTimer, m_sprite[30].h*(m_PosY + 1) + m_AnimationTimer, renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1) + m_AnimationTimer, m_sprite[31].h*(m_PosY + 1) + m_AnimationTimer, renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer -= 4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorUpRight(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX - m_AnimationTimer, m_sprite[20].h*m_PosY + m_AnimationTimer, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1) - m_AnimationTimer, m_sprite[21].h*m_PosY + m_AnimationTimer, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX - m_AnimationTimer, m_sprite[30].h*(m_PosY + 1) + m_AnimationTimer, renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1) - m_AnimationTimer, m_sprite[31].h*(m_PosY + 1) + m_AnimationTimer, renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer -= 4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorDown(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX, m_sprite[20].h*m_PosY - m_AnimationTimer, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1), m_sprite[21].h*m_PosY - m_AnimationTimer, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX, m_sprite[30].h*(m_PosY + 1) - m_AnimationTimer, renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1), m_sprite[31].h*(m_PosY + 1) - m_AnimationTimer, renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer-=4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorDownLeft(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX + m_AnimationTimer, m_sprite[20].h*m_PosY - m_AnimationTimer, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1) + m_AnimationTimer, m_sprite[21].h*m_PosY - m_AnimationTimer, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX + m_AnimationTimer, m_sprite[30].h*(m_PosY + 1) - m_AnimationTimer, renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1) + m_AnimationTimer, m_sprite[31].h*(m_PosY + 1) - m_AnimationTimer, renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer -= 4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorDownRight(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX - m_AnimationTimer, m_sprite[20].h*m_PosY - m_AnimationTimer, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1) - m_AnimationTimer, m_sprite[21].h*m_PosY - m_AnimationTimer, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX - m_AnimationTimer, m_sprite[30].h*(m_PosY + 1) - m_AnimationTimer, renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1) - m_AnimationTimer, m_sprite[31].h*(m_PosY + 1) - m_AnimationTimer, renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer -= 4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorLeft(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX + m_AnimationTimer, m_sprite[20].h*m_PosY, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1) + m_AnimationTimer, m_sprite[21].h*m_PosY, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX + m_AnimationTimer, m_sprite[30].h*(m_PosY + 1), renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1) + m_AnimationTimer, m_sprite[31].h*(m_PosY + 1), renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer-=4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}

void Hosono::moveCursorRight(Renderer* renderer, Renderable* renderable, SDL_Rect* viewport)
{
	if (m_AnimationTimer > 0) {
		renderer->render(m_sprite[20].w*m_PosX - m_AnimationTimer, m_sprite[20].h*m_PosY, renderable->getRenderable(), &m_sprite[20], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[21].w*(m_PosX + 1) - m_AnimationTimer, m_sprite[21].h*m_PosY, renderable->getRenderable(), &m_sprite[21], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[30].w*m_PosX - m_AnimationTimer, m_sprite[30].h*(m_PosY + 1), renderable->getRenderable(), &m_sprite[30], viewport, 0, NULL, m_Flip);
		renderer->render(m_sprite[31].w*(m_PosX + 1) - m_AnimationTimer, m_sprite[31].h*(m_PosY + 1), renderable->getRenderable(), &m_sprite[31], viewport, 0, NULL, m_Flip);
		m_AnimationTimer-=4;
	}
	else { m_MoveState = 0; m_AnimationTimer = 32; }
}