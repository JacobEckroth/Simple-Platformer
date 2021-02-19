#include "Button.h"
#include <iostream>
#include <string>
#include "Window.h"

void Button::render() {
	if (buttonActive) {
		SDL_RenderCopy(Window::renderer, buttonActiveImage, NULL, &buttonRect);
	}
	else {
		SDL_RenderCopy(Window::renderer, buttonInactiveImage, NULL, &buttonRect); 
	}
}


bool Button::mouseInButton(int x, int y) {
	if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
		return true;
	}
	return false;

}




void Button::loadImages(std::string buttonInactiveString, std::string buttonActiveString) {
	SDL_Surface* activeSurface = IMG_Load(buttonActiveString.c_str());
	SDL_Surface* inactiveSurface = IMG_Load(buttonInactiveString.c_str());
	buttonActiveImage = SDL_CreateTextureFromSurface(Window::renderer,activeSurface);
	buttonInactiveImage = SDL_CreateTextureFromSurface(Window::renderer, inactiveSurface);
	SDL_FreeSurface(activeSurface);
	SDL_FreeSurface(inactiveSurface);



}

void Button::updateButtonActive(bool newActive) {
	buttonActive = newActive;
}



Button::~Button() {
	SDL_DestroyTexture(buttonActiveImage);
	SDL_DestroyTexture(buttonInactiveImage);
}

void Button::init(std::string buttonInactiveString, std::string buttonActiveString, int buttonX, int buttonY, int buttonHeight) {
	buttonRect.x = buttonX;
	buttonRect.y = buttonY;
	loadImages(buttonInactiveString, buttonActiveString);
	int w, h;
	SDL_QueryTexture(buttonActiveImage, NULL, NULL, &w, &h);
	
	ratio = float(w) / h;

	buttonRect.h = buttonHeight;
	buttonRect.w = buttonHeight * ratio;
	
	buttonActive = false;

}

void Button::updateButtonSize(int x, int y, int newH) {
	buttonRect.x = x;
	buttonRect.y = y;
	
	buttonRect.h = newH;
	buttonRect.w = newH * ratio;
}