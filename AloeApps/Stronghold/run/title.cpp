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

	m_Font = new TrueType(renderer);
	m_Font->setFont("AloeApps/StrongHold/Media/NiseSega.ttf", 70);

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

	m_Button.push_back(Button((m_Width / 2) - (4 * m_Sprite[3].w), m_Height / 2, 7, 3, 40, "DEBUG",m_SpriteSheet,m_Font,m_Window,m_Renderer));
	m_Button[0].setEffect(1,{ 0xFF, 0xFF, 0xFF });
	m_Button.push_back(Button(8 * m_Sprite[3].w, 0, 7, 3,40, "TESTS", m_SpriteSheet, m_Font, m_Window, m_Renderer));
	m_Button[1].setEffect(1, { 0xFF, 0xFF, 0xFF });
	m_Button.push_back(Button(m_Width - (8 * m_Sprite[3].w), 0 + (4 * m_Sprite[3].h), 7, 3,40, "ROLL_MAP", m_SpriteSheet, m_Font, m_Window, m_Renderer));
	m_Button[2].setEffect(1, { 0xFF, 0xFF, 0xFF });
	m_Button.push_back(Button(m_Width - (8 * m_Sprite[3].w), 0 + (8 * m_Sprite[3].h), 7, 3,40, "MUSIC_ROOM", m_SpriteSheet, m_Font, m_Window, m_Renderer));
	m_Button[3].setEffect(1, { 0xFF, 0xFF, 0xFF });
	//m_Button.push_back(Button(m_Width / 2 - (4 * m_Sprite[3].w), m_Height / 2, 7, 3, 40, "DEBUG", m_SpriteSheet, m_Font, m_Window, m_Renderer));

	m_ViewPort.x = 0;
	m_ViewPort.y = 0;
	m_ViewPort.w = width;
	m_ViewPort.h = height;

}

Title::~Title()
{
	delete m_Maths;
	delete m_SpriteSheet;
	delete m_MootSheet;
	delete m_Font;
	std::cout << "Title DELETED!"<< std::endl;
}

int Title::run()
{
	int control;
	switch (m_State)
	{
		case 0:
			if (front()) { m_State = 1;}
			break;

		case 1:
			control = menu();
			if (control==1) { return 1; }
			if (control == 2) { return 2; }
			if (control == 3) { return 3; }
			if (control == 9) { m_State=0; }
			break;
	}

	//std::cout << m_Frame << "," << m_HalfFrame << std::endl;

	return 0;
}

bool Title::front()
{
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	int offset = 0;

	SDL_RenderSetScale(m_Renderer->getRenderer(), m_Width / 160, m_Width / 160);
	m_Renderer->render(10, 10 + round((2 * m_Maths->sinWave(0, 60, m_Window->getFrame()/2))), m_SpriteSheet->getRenderable(), &m_Sprite[0], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render(50, 10 + round((2 * m_Maths->sinWave(0, 60, m_Window->getFrame()/2))), m_SpriteSheet->getRenderable(), &m_Sprite[1], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render(90, 10 + round((2 * m_Maths->sinWave(0, 60, m_Window->getFrame()/2))), m_SpriteSheet->getRenderable(), &m_Sprite[2], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	m_Renderer->render(130, 10 + round((2 * m_Maths->sinWave(0, 60,m_Window->getFrame()/2))), m_SpriteSheet->getRenderable(), &m_Sprite[3], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);

	//printf("Frame:  %i\n", m_Window->getFrame());
	if (m_Button[0].render(&m_ViewPort)){return true;}

	//Moot Loop
	SDL_RenderSetScale(m_Renderer->getRenderer(),1,1);
	m_Renderer->render((m_Width / 2) + (3 * m_Sprite[3].w), m_Height / 2, m_MootSheet->getRenderable(), &m_SSprite[21 + ((m_Window->getFrame()%60)/12)], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);

	//if (label(m_Width/2 - (4 * m_Sprite[3].w), m_Height/2, 7, 3, "DEBUG")) { return true; }

	return false;
}

int Title::menu()
{
	//if (label(m_Width- (8 * m_Sprite[3].w), 0, 7, 3, "TESTS")) { return 1; }
	//if (label(m_Width - (8 * m_Sprite[3].w), 0+(4 * m_Sprite[3].h), 7, 3, "ROLL MAP")) { return 2; }
	//if (label(m_Width - (8 * m_Sprite[3].w), 0 + (8 * m_Sprite[3].h), 7, 3, "MUSIC ROOM")) { return 3; }
	if (m_Button[1].render(&m_ViewPort)){return 1;}
	if (m_Button[2].render(&m_ViewPort)){return 2;}
	if (m_Button[3].render(&m_ViewPort)){return 3;}

	//if (label(0, m_Height - (3 * m_Sprite[3].h), 2, 2, " ")) { return 9; }
	SDL_RenderSetScale(m_Renderer->getRenderer(), 1, 1);
	m_Renderer->render(0 + (1 * m_Sprite[3].h), m_Height - (2 * m_Sprite[3].h), m_SpriteSheet->getRenderable(), &m_Sprite[20], &m_ViewPort, 0, NULL, SDL_FLIP_NONE);
	return 0;
}

