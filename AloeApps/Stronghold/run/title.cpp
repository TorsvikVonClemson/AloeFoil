#include "title.h"

Title::Title(int width,int height, Renderer* renderer, Window* window)
{
	m_Width = width;
	m_Height = height;
	m_Renderer = renderer;
	m_Window = window;

	m_Maths = new Maths();

	m_SpriteSheet=new Renderable("AloeApps/StrongHold/Media/ForeverAlphaSTitle.png", renderer->getRenderer(), width, height);
	m_MootSheet= new Renderable("AloeApps/StrongHold/Media/MootTest00.png", renderer->getRenderer(), width, height);

	m_SEGAFont = new TrueType(renderer);
	m_SEGAFont->setFont("AloeApps/StrongHold/Media/NiseSega.ttf", 70);

	m_ViewPort.x = 0;
	m_ViewPort.y = 0;
	m_ViewPort.w = width;
	m_ViewPort.h = height;

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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_SSprite[i + j * 10].x = 16 * i;
			m_SSprite[i + j * 10].y = 16 * j;
			m_SSprite[i + j * 10].w = 16;
			m_SSprite[i + j * 10].h = 16;
		}
	}
}

Title::~Title()
{
	delete m_Maths;
	delete m_SpriteSheet;
	delete m_MootSheet;
	delete m_SEGAFont;
	std::cout << "Title DELETED!"<< std::endl;
}

int Title::run()
{
	int control;
	switch (m_State)
	{
		case 0:
			if (front()) { m_State = 1; m_Frame = 0;}
			break;

		case 1:
			control = menu();
			if (control==1) { return 1; }
			if (control == 2) { return 2; }
			if (control == 9) { m_State=0; }
			break;
	}

	if (m_Frame == 60) { m_Frame = 0; }
	if (m_Frame % 3 == 0) { m_HalfFrame++; }
	if (m_HalfFrame == 60) { m_HalfFrame = 0; }
	m_Frame++;

	//std::cout << m_Frame << "," << m_HalfFrame << std::endl;

	return 0;
}

bool Title::front()
{
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	int offset = 0;

	SDL_RenderSetScale(m_Renderer->getRenderer(), m_Width / 160, m_Width / 160);
	m_Renderer->render(10, 10 + round((2 * m_Maths->sinWave(0, 60, m_HalfFrame))), m_SpriteSheet->getRenderable(), &m_Sprite[0], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render(50, 10 + round((2 * m_Maths->sinWave(0, 60, m_HalfFrame))), m_SpriteSheet->getRenderable(), &m_Sprite[1], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render(90, 10 + round((2 * m_Maths->sinWave(0, 60, m_HalfFrame))), m_SpriteSheet->getRenderable(), &m_Sprite[2], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render(130, 10 + round((2 * m_Maths->sinWave(0, 60, m_HalfFrame))), m_SpriteSheet->getRenderable(), &m_Sprite[3], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);

	//Moot Loop
	SDL_RenderSetScale(m_Renderer->getRenderer(),1,1);
	m_Renderer->render((m_Width / 2) + (3 * m_Sprite[3].w), m_Height / 2, m_MootSheet->getRenderable(), &m_SSprite[21 + (m_Frame / 12)], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);

	if (label(m_Width/2 - (4 * m_Sprite[3].w), m_Height/2, 7, 3, "DEBUG")) { return true; }

	return false;
}

int Title::menu()
{
	if (label(m_Width- (8 * m_Sprite[3].w), 0, 7, 3, "TESTS")) { return 1; }
	if (label(m_Width - (8 * m_Sprite[3].w), 0+(4 * m_Sprite[3].h), 7, 3, "ROLL MAP")) { return 2; }
	if (label(m_Width - (8 * m_Sprite[3].w), 0 + (8 * m_Sprite[3].h), 7, 3, "MUSIC ROOM")) { return 2; }

	if (label(0, m_Height - (3 * m_Sprite[3].h), 2, 2, " ")) { return 9; }
	SDL_RenderSetScale(m_Renderer->getRenderer(), 1, 1);
	m_Renderer->render(0 + (1 * m_Sprite[3].h), m_Height - (2 * m_Sprite[3].h), m_SpriteSheet->getRenderable(), &m_Sprite[20], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	return 0;
}

bool Title::button(Window * window, int xMin, int xMax, int yMin, int yMax)
{


	if (m_Maths->findRect(window, xMin, xMax, yMin, yMax))
	{
		m_Highlight = true;
		if (m_Window->getMouseButton() == SDL_BUTTON_LEFT  && !m_MouseHeld)
		{
			m_MouseHeld = true;
			return true;
		}
		else if(!m_Window->getMouseButton() == SDL_BUTTON_LEFT && m_MouseHeld)
		{
			m_MouseHeld = false;
		}
		return false;
	}
	else {
		if (m_Window->getMouseButton() == SDL_BUTTON_LEFT && !m_MouseHeld)
		{
			m_MouseHeld = true;

		}
		else if (!m_Window->getMouseButton() == SDL_BUTTON_LEFT && m_MouseHeld)
		{
			m_MouseHeld = false;
		}
	}
	m_Highlight = false;
	return false;
}

bool Title::label(int xPos, int yPos, int xWidth, int yHeight, std::string text)
{
	// Width and height is taken as length-1

	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	int offset = 0;

	SDL_RenderSetScale(m_Renderer->getRenderer(), 1, 1);

	//Top Left
	m_Renderer->render(xPos, yPos, m_SpriteSheet->getRenderable(), &m_Sprite[10], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	
	//Horizontal Top
	for (int i = xWidth-1; i > 0; i--)
	{
		m_Renderer->render(xPos+ (i * m_Sprite[3].w), yPos, m_SpriteSheet->getRenderable(), &m_Sprite[11], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	}

	//Top Right
	m_Renderer->render(xPos + (xWidth * m_Sprite[3].w), yPos, m_SpriteSheet->getRenderable(), &m_Sprite[10], &m_ViewPort, 90, NULL, SDL_FLIP_NONE);

	//Vertical Right
	for (int i = yHeight-1; i > 0; i--)
	{
		m_Renderer->render(xPos+ (xWidth * m_Sprite[3].w), (yPos) + (i * m_Sprite[3].w), m_SpriteSheet->getRenderable(), &m_Sprite[11], &m_ViewPort, 90, NULL, SDL_FLIP_NONE);
	}

	//Vertical Left
	for (int i = yHeight-1; i > 0; i--)
	{
		m_Renderer->render(xPos, (yPos) + (i * m_Sprite[3].w), m_SpriteSheet->getRenderable(), &m_Sprite[11], &m_ViewPort, 270, NULL, SDL_FLIP_NONE);
	}

	//Bottom Left
	m_Renderer->render(xPos, (yPos) + (yHeight * m_Sprite[3].w), m_SpriteSheet->getRenderable(), &m_Sprite[10], &m_ViewPort, 270, NULL, SDL_FLIP_NONE);

	//Horizontal Bottom
	for (int i = xWidth-1; i > 0; i--)
	{
		m_Renderer->render(xPos + (i * m_Sprite[3].w), (yPos) + (yHeight * m_Sprite[3].w), m_SpriteSheet->getRenderable(), &m_Sprite[11], &m_ViewPort, 180, NULL, SDL_FLIP_NONE);
	}

	//Bottom Right
	m_Renderer->render(xPos + (xWidth * m_Sprite[3].w), (yPos) + (yHeight * m_Sprite[3].w), m_SpriteSheet->getRenderable(), &m_Sprite[10], &m_ViewPort, 180, NULL, SDL_FLIP_NONE);

	//Text
	if (button(m_Window, xPos, xPos+(xWidth * m_Sprite[3].w), yPos, yPos+(yHeight * m_Sprite[3].w))) { return true; }

	float length = text.length();
	float resize = 5 / length;
	std::cout << resize << std::endl;
	int hardSize = m_Sprite[3].w;
	SDL_RenderSetScale(m_Renderer->getRenderer(), resize, resize);
	if (!m_Highlight)
	{
		m_SEGAFont->loadFromRenderedText(text, textColor,((xPos)+(1 * m_Sprite[3].w)) / resize, (yPos + (1.25 * hardSize))/resize + 5/resize, m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
	}
	else
	{
		std::string single;
		for (unsigned i = 0; i < text.length(); ++i)
		{
			single = text.at(i);
			m_SEGAFont->loadFromRenderedText( (single), textColor, ((xPos)+(1 * hardSize)) / resize + offset, (yPos + (1.25 * hardSize))/resize + 5/ resize + round((8 * m_Maths->sinWave(0, 60,(i*12)+ m_HalfFrame * 2))), m_Width, NULL, 0, NULL, SDL_FLIP_NONE);
			offset += m_SEGAFont->getWidth();
		}
	}

	return false;
}
