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

	void updateButtonSize();
	void updateButtonPosition(int x, int y);
	void init(std::string inactiveString, std::string activeString, int x, int y, float boxesH);
	int getWidth();
	int getHeight();
	void setY(int);
	void setX(int);
	int getX();
	int getY();
	void setFunction();
private:


	SDL_Rect buttonRect;
	bool buttonActive;

	float ratio;		//this is equal to W/H

	float boxesHeight;

	SDL_Texture* buttonActiveImage;
	SDL_Texture* buttonInactiveImage;

	//voidFunction function;

};

