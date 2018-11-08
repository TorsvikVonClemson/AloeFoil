#include "Graphics\Window\window.h"
#include "Graphics\Window\timer.h"
#include "Graphics\Natives\native.h"
#include "Graphics\Rendering\Renderer.h"
#include "Graphics\Rendering\Renderable.h"
#include "Graphics\Natives\hexagon.h"
#include "Graphics\Rendering\trueType.h"
#include "TestApps\sheetTest.h"
#include "TestApps\mapTest.h"
#include "TestApps\Hosono.h"

#include "..\..\AloeApps\Stronghold\debug\debug.h"
#include "..\..\AloeApps\Stronghold\run\run.h"

#include "music.h"

#include <SDL.h> 

#include <string>
#include <time.h>
#include <iostream>
#include <sstream>

#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SHEET_SIZE 160

//Without buffer swapping, the importance of Window.update is questionable. I'll let it stand as a canard.

//TODOs
//In order to make width & height variable I need to mak the arrays dependant on them to be dynamic 

int main(int argc, char* args[])
{
	  
	Window window("Aloe Foil", SCREEN_WIDTH, SCREEN_HEIGHT);
	Renderer renderer(window.getWindow());
	//Native native(SCREEN_WIDTH, SCREEN_HEIGHT, &renderer);
	Timer ticks;
	Timer frames;

	//Renderable testSheet("Media/testsheet04.png", renderer.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
	//Renderable mootTest("Media/MootTest00.png", renderer.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
	//Renderable test02("Media/FlatColourTest00.png", renderer.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
	//Renderable test03("Media/Flower00.png", renderer.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
	//Renderable hexSprites("Media/HexSprites.png", renderer.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
	//Renderable title("Media/ForeverAlphaSTitle.png", renderer.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

	//TrueType text(&renderer);
	//SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	//text.setFont("Media/NiseSega.ttf", 70);

	//define viewports

	//SDL_Rect defaultViewPort;
	//defaultViewPort.x = 0;
	//defaultViewPort.y = 0;
	//defaultViewPort.w= SCREEN_WIDTH;
	//defaultViewPort.h = SCREEN_HEIGHT;

	//SDL_Rect zoomViewPort;
	//zoomViewPort.x = SCREEN_WIDTH/2;
	//zoomViewPort.y = SCREEN_HEIGHT/2;
	//zoomViewPort.w = SCREEN_WIDTH;
	//zoomViewPort.h = SCREEN_HEIGHT;

	//SheetTest sheetTest(SCREEN_WIDTH,SCREEN_HEIGHT);
	//MapTest mapTest(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Hosono hosono(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Hexagon hexTest(SCREEN_WIDTH, SCREEN_HEIGHT,&window,&renderer);
	
	//Debug *debug=new Debug(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer,&native,&hexSprites,&defaultViewPort);

	//int frame = 0;
	//SDL_Event e;
	//SDL_Point mPosition;
	float avgFPS = 0;
	
	int countedFrames = 0;
	ticks.start();
	
	int i = 0;

	Run stronghold(SCREEN_WIDTH,SCREEN_HEIGHT,&window,&renderer);
	Music music;

	music.loadMusic();

	while (!window.isClosed())
	{
	//
	//	frames.start();
		window.update();
	//	//SDL_ShowCursor(SDL_DISABLE);
	//	//SDL_SetRelativeMouseMode(SDL_TRUE);
	//	//Handle Inputs
	//
	//	//std::cout << mouse.getPosition().x<<","<< mouse.getPosition().y <<std::endl;
	//
		renderer.clear();
	//
		

	//	//sheetTest.run(&window,&renderer,&testSheet, &defaultViewPort);
	//	//mapTest.run(&window, &renderer,&test02, &defaultViewPort);
	//	hosono.run(&window, &renderer, &test03, &defaultViewPort);
	//	
	//	debug->run();
		stronghold.controlSwitcher();
	//
	//	//text.loadFromRenderedText("Testing...", textColor,0,0,NULL,0,NULL, SDL_FLIP_NONE);
	//
	//
	//
		renderer.display();
	
		avgFPS = countedFrames / (ticks.getTicks() / 1000.f); if (avgFPS > 2000000) { avgFPS = 0; }
		++countedFrames;
		if (frames.getTicks() < 1000 / 60) { SDL_Delay(1000 / 60 - frames.getTicks()); }
		std::cout << "Avg FPS: " << avgFPS << std::endl;
	//	i+=.05;
	
	}

	//delete debug;

	return 0;
}
