#pragma once
#include "SDL.h"
class WinRect
{
private:
	SDL_Rect drawRect;
	int boxesX;
	int boxesY;
	int boxesWidth;
	int boxesHeight;
	
public:
	static SDL_Color winColor;
	void init(int, int, int, int);
	void render();
	SDL_Rect getHitbox();
	void resizeBox();
	int getBoxesX();
	int getBoxesY();
	int getBoxesWidth();
	int getBoxesHeight();
};

