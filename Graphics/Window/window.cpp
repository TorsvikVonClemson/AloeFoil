#include "window.h"

Window::Window(const char *title, int width, int height)
{
	m_Title = title;
	m_Width = width;
	m_Height = height;
	m_CurrentKeyStates = NULL;
	m_Ticks= new Timer;
	m_Frames = new Timer;
	init();
	m_Ticks->start();
}

Window::~Window()
{
	SDL_FreeSurface(m_ImageMedia);
	m_ImageMedia = NULL;

	SDL_DestroyWindow(m_Window);
	m_Window = NULL;

	SDL_Quit();
}

SDL_Window* Window::getWindow()
{
	return m_Window;
}

const Uint8* Window::getKeyPressed()
{
	return m_CurrentKeyStates;
}

int Window::getWidth()
{
	return m_Width;
}

int Window::getMousePosX()
{
	return m_MousePosX;
}

int Window::getMousePosY()
{
	return m_MousePosY;
}

int Window::getFrame()
{
	return m_CurrentFrame;
}

bool Window::getMouseButton()
{
	return m_MouseDown;
}

SDL_Surface* Window::loadSurface(const char *image)
{
	m_ImageMedia = IMG_Load(image); 
	SDL_Surface* optimizedSurface = NULL;

	if (m_ImageMedia == NULL)
	{
		printf("Unable to load image %s\n! SDL_Error: %s\n",image, SDL_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(m_ImageMedia, m_ScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", image, SDL_GetError());
		}
		SDL_FreeSurface(m_ImageMedia);
	}

	return optimizedSurface;



}


bool Window::isClosed()
{
	return m_IsClosed;
}

void Window::setFrame(int f)
{
	//manually set the current frame
	m_CurrentFrame = f;
}

void Window::close()
{
	SDL_FreeSurface(m_ImageMedia);
	m_ImageMedia = NULL;

	SDL_DestroyWindow(m_Window);
	m_Window = NULL;

	SDL_Quit();
	m_IsClosed = true;
}

void Window::update()//updates keys and frames
{

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT) {close();}
		m_Mouse.handleEvent(&e);
		m_CurrentKeyStates = SDL_GetKeyboardState(NULL);
		//std::cout << m_Mouse.getPosition().x << "," << m_Mouse.getPosition().y << std::endl;
		m_MousePosX = m_Mouse.getPosition().x;
		m_MousePosY = m_Mouse.getPosition().y;
		m_MouseDown = m_Mouse.getButton();
	}

	int i = 0;

	m_AvgFPS = m_CurrentFrame / (m_Ticks->getTicks() / 1000.f); if (m_AvgFPS > 2000000) { m_AvgFPS = 0; }
	++m_CurrentFrame;
	if (m_Frames->getTicks() < 1000 / 60) { SDL_Delay(1000 / 60 - m_Frames->getTicks()); }
	//std::cout << "Avg FPS: " << avgFPS << std::endl;
}

bool Window::init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//create window
		m_Window = SDL_CreateWindow("AloeFoil", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (m_Window == NULL)
		{
			printf("Window failed to initialize! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			printf("Window initialized!");
		}		
	}

	m_ScreenSurface = SDL_GetWindowSurface(m_Window);
	SDL_FillRect(m_ScreenSurface, NULL, SDL_MapRGB(m_ScreenSurface->format, 0x00, 0x00, 0xAA));

	return true;
}
