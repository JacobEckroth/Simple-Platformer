#pragma once]
#include "SDL.h"
#include "SDL_image.h"
#include <string>
class Button
{
public:
	void render();
	bool mouseInButton(int,int);
	
	void loadImages(std::string, std::string);

	void updateButtonActive(bool );
	~Button();

	void updateButtonSize(int x, int y, int newH);

	void init(std::string inactiveString, std::string activeString, int x,int y ,int h);

private:


	SDL_Rect buttonRect;
	bool buttonActive;

	float ratio;		//this is equal to W/H


	SDL_Texture* buttonActiveImage;
	SDL_Texture* buttonInactiveImage;
};

