#pragma once
#include <SDL.h>

class RectanglePlatform
{

public:

	void render();
	void init(int, int, int, int, SDL_Color);
	SDL_Rect getHitbox();
	SDL_Color getColor();
	bool mouseInPlatform(int x, int y);
	void resizeBox();
private:

	SDL_Color color;

	SDL_Rect drawRect;
	


	SDL_Rect hitbox;

	int boxesX;
	int boxesY;
	int boxesWidth;
	int boxesHeight;
};

