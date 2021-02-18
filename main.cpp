#include "Window.h"
#include "SDL.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <ctime>
#include <crtdbg.h>
#include <iostream>
 int main() {
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart = SDL_GetTicks();
	int frameTime = 0;
	Window* gameWindow = new Window;
	
	float deltaTime;


	gameWindow->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
	while (gameWindow->running()) {
		deltaTime = SDL_GetTicks() - frameStart;
		frameStart = SDL_GetTicks();
		gameWindow->handleEvents();
		gameWindow->update(float(deltaTime) / 1000.0);
		gameWindow->render();
		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	gameWindow->clean();
	delete gameWindow;



	_CrtDumpMemoryLeaks();
	return 0;
}