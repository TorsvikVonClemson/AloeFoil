/*
PRE_MODE KEY 
0: NewTests
1: Stronghold
2: Cagiyama
*/

#define PRE_MODE 1

#include <string>

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


int main(int argc, char* args[])
{
	  
	Window window("Aloe Foil", SCREEN_WIDTH, SCREEN_HEIGHT);
	Renderer renderer(window.getWindow());

#if PRE_MODE==1
	Run stronghold(SCREEN_WIDTH,SCREEN_HEIGHT,&window,&renderer);
#elif PRE_MODE==2
	TimedCounter timedCounter(1000, 200, &window, &renderer);
#endif
	
	while (!window.isClosed())
	{
		window.update();
		renderer.clear();
#if PRE_MODE==1
		stronghold.controlSwitcher();
#elif PRE_MODE==2
		timedCounter.run(window.getFrame());
#endif

		renderer.display();
	}
	return 0;
}
