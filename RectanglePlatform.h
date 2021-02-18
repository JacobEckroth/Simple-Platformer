#pragma once
#include <SDL.h>

class RectanglePlatform
{

public:

	void render();
	void init(int, int, int, int, SDL_Color);
	SDL_Rect getHitbox();
	SDL_Color getColor();
private:

	SDL_Color color;
	SDL_Rect drawRect;
	SDL_Rect hitbox;
};

