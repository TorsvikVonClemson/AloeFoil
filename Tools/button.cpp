#include "button.h"

Button::Button(int x, int y, int w, int h, int spriteSize, std::string text, Renderable* sheet, TrueType* font, Window* window, Renderer* renderer)
{
	m_X = x;
	m_Y = y;
	m_W = w;
	m_H = h;
	m_SpriteSize = spriteSize;

	m_Text = text;
	m_Font = font;
	m_Window = window;
	m_Renderer = renderer;
	m_Sheet = sheet;
	m_Maths = new Maths();

	m_Effect = 0;

	//define sprite sheet
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_Sprite[i + j * 10].x = spriteSize * i;
			m_Sprite[i + j * 10].y = spriteSize * j;
			m_Sprite[i + j * 10].w = spriteSize;
			m_Sprite[i + j * 10].h = spriteSize;
		}
	}
}

Button::~Button()
{
}

void Button::setEffect(int effect, SDL_Color textColor)
{
	/*Effects will have various settings that will be progressively added as needed.
	
	0: No Effect
	1: Wavey Text*/
	m_Effect = effect;
	m_TextColor = textColor;

}

bool Button::render(SDL_Rect* viewPort)
{
	int offset = 0;
	

	SDL_RenderSetScale(m_Renderer->getRenderer(), 1, 1);

	//Top Left
	m_Renderer->render(m_X, m_Y, m_Sheet->getRenderable(), &m_Sprite[10], viewPort, 0, NULL, SDL_FLIP_NONE);

	//Horizontal Top
	for (int i = m_W - 1; i > 0; i--)
	{
		m_Renderer->render(m_X + (i * m_Sprite[3].w), m_Y, m_Sheet->getRenderable(), &m_Sprite[11], viewPort, 0, NULL, SDL_FLIP_NONE);
	}

	//Top Right
	m_Renderer->render(m_X + (m_W * m_Sprite[3].w), m_Y, m_Sheet->getRenderable(), &m_Sprite[10], viewPort, 90, NULL, SDL_FLIP_NONE);

	//Vertical Right
	for (int i = m_H - 1; i > 0; i--)
	{
		m_Renderer->render(m_X + (m_W * m_Sprite[3].w), (m_Y)+(i * m_Sprite[3].w), m_Sheet->getRenderable(), &m_Sprite[11], viewPort, 90, NULL, SDL_FLIP_NONE);
	}

	//Vertical Left
	for (int i = m_H - 1; i > 0; i--)
	{
		m_Renderer->render(m_X, (m_Y)+(i * m_Sprite[3].w), m_Sheet->getRenderable(), &m_Sprite[11], viewPort, 270, NULL, SDL_FLIP_NONE);
	}

	//Bottom Left
	m_Renderer->render(m_X, (m_Y)+(m_H * m_Sprite[3].w), m_Sheet->getRenderable(), &m_Sprite[10], viewPort, 270, NULL, SDL_FLIP_NONE);

	//Horizontal Bottom
	for (int i = m_W - 1; i > 0; i--)
	{
		m_Renderer->render(m_X + (i * m_Sprite[3].w), (m_Y)+(m_H * m_Sprite[3].w), m_Sheet->getRenderable(), &m_Sprite[11], viewPort, 180, NULL, SDL_FLIP_NONE);
	}

	//Bottom Right
	m_Renderer->render(m_X + (m_W * m_Sprite[3].w), (m_Y)+(m_H * m_Sprite[3].w), m_Sheet->getRenderable(), &m_Sprite[10], viewPort, 180, NULL, SDL_FLIP_NONE);

	//Text

	float length = m_Text.length();
	float resize = 5 / length;
	int hardSize = m_Sprite[3].w;
	SDL_RenderSetScale(m_Renderer->getRenderer(), resize, resize);
	if (m_Effect==1 && m_Highlight)
	{
		std::string single;
		for (unsigned i = 0; i < m_Text.length(); ++i)
		{
			single = m_Text.at(i);
			m_Font->loadFromRenderedText(single, m_TextColor, ((m_X)+(1 * hardSize)) / resize + offset,
				(m_Y + (1.25 * hardSize)) / resize + 5 / resize + round((8 * m_Maths->sinWave(0, 60, (i * 12) + m_Window->getFrame()))), 
				m_Window->getWidth(), NULL, 0, NULL, SDL_FLIP_NONE);
			offset += m_Font->getWidth();
		}
	}
	else
	{
		m_Font->loadFromRenderedText(m_Text, m_TextColor, ((m_X)+(1 * m_Sprite[3].w)) / resize, (m_Y + (1.25 * hardSize)) / resize + 5 / resize, m_W, NULL, 0, NULL, SDL_FLIP_NONE);
	}
	return events();//returns true if it has been pressd while setting other flags
}

bool Button::events()
{

	if (m_Maths->findRect(m_Window, m_X, m_X+((1+m_W)*m_SpriteSize), m_Y, m_Y + ((1+m_H)*m_SpriteSize)))
	{
		m_Highlight = true;
		if (m_Window->getMouseButton() == SDL_BUTTON_LEFT && !m_MouseHeld) //the button has been clicked proper
		{
			m_MouseHeld = true;
			return true;
		}
		else if (!m_Window->getMouseButton() == SDL_BUTTON_LEFT && m_MouseHeld)
		{
			m_MouseHeld = false;
		}
		return false;
	}

	m_Highlight = false;
	return false;
}

