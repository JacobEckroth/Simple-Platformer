#include "WinRect.h"
#include "Level.h"
#include "Window.h"
#include "Game.h"
#include <iostream>
SDL_Color WinRect::winColor;

void WinRect::init(int newBoxesX, int newBoxesY, int newBoxesWidth, int newBoxesHeight) {
	boxesX = newBoxesX;
	boxesY = newBoxesY;
	boxesWidth = newBoxesWidth;	
	boxesHeight = newBoxesHeight;

	drawRect.x = Game::topLeftX + boxesX * Level::boxRect.w;
	drawRect.y = Game::topLeftY + boxesY * Level::boxRect.h;
	drawRect.w = boxesWidth * Level::boxRect.w;
	drawRect.h = boxesHeight * Level::boxRect.h;

}



void WinRect::render() {
	
	SDL_SetRenderDrawColor(Window::renderer, winColor.r, winColor.g, winColor.b, winColor.a);
	SDL_RenderFillRect(Window::renderer, &drawRect);
}

SDL_Rect WinRect::getHitbox() {
	return drawRect;
}

void WinRect::resizeBox() {
	drawRect.x = Game::topLeftX + boxesX * Level::boxRect.w;
	drawRect.y = Game::topLeftY + boxesY * Level::boxRect.h;
	drawRect.w = boxesWidth * Level::boxRect.w;
	drawRect.h = boxesHeight * Level::boxRect.h;
}

int WinRect::getBoxesHeight() {
	return boxesHeight;
}

int WinRect::getBoxesWidth() {
	return boxesWidth;
}

int WinRect::getBoxesX() {
	return boxesX;
}

int WinRect::getBoxesY() {
	return boxesY;
}