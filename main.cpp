/*
PRE_MODE KEY 
0: NewTests
1: Stronghold
2: Cagiyama
*/
#define PRE_MODE 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include <string>
#include <time.h>
#include <iostream>
#include <sstream>

#include "Graphics\Window\window.h"
#include "Graphics\Window\timer.h"
#include "Graphics\Rendering\Renderer.h"

#if PRE_MODE==1
#include "..\..\AloeApps\Stronghold\debug\debug.h"
#include "..\..\AloeApps\Stronghold\run\run.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#elif PRE_MODE==2
#include "AloeApps\Cagiyama\timedCounter.h"
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 200

#endif

//#include "music.h"


int main(int argc, char* args[])
{
	  
	Window window("Aloe Foil", SCREEN_WIDTH, SCREEN_HEIGHT);
	Renderer renderer(window.getWindow());
	Timer ticks;
	Timer frames;

	float avgFPS = 0;	
	int countedFrames = 0;
	ticks.start();	
	int i = 0;

#if PRE_MODE==1
	Run stronghold(SCREEN_WIDTH,SCREEN_HEIGHT,&window,&renderer);
#elif PRE_MODE==2
	TimedCounter timedCounter(1000, 200, &window, &renderer);
#endif
	
	//	Music music;

	//music.loadMusic();

	while (!window.isClosed())
	{
		window.update();
	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
		renderer.clear();
#if PRE_MODE==1
		stronghold.controlSwitcher();
#elif PRE_MODE==2
		timedCounter.run(countedFrames);
#endif

		renderer.display();
	
		avgFPS = countedFrames / (ticks.getTicks() / 1000.f); if (avgFPS > 2000000) { avgFPS = 0; }
		++countedFrames;
		if (frames.getTicks() < 1000 / 60) { SDL_Delay(1000 / 60 - frames.getTicks()); }
		//std::cout << "Avg FPS: " << avgFPS << std::endl;
	
	}
	return 0;
}
