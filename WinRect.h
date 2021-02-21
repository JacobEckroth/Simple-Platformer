#pragma once
#include "SDL.h"
#include <string>
class WinRect
{
private:
	SDL_Rect drawRect;
	int boxesX;
	int boxesY;
	int boxesWidth;
	int boxesHeight;
	SDL_Texture* winDoorImage;
	float ratio;
	
public:
	static SDL_Color winColor;
	void init(int, int, int, int, std::string fileName);
	void render();
	SDL_Rect getHitbox();
	void resizeBox();
	int getBoxesX();
	int getBoxesY();
	int getBoxesWidth();
	int getBoxesHeight();
	~WinRect();
	void setBoxesX(int x);
	void setBoxesY(int y);
};

