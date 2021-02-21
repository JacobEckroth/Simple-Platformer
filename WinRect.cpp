#include "WinRect.h"
#include "Level.h"
#include "Window.h"
#include "Game.h"
#include <iostream>
#include "TextureManager.h"
SDL_Color WinRect::winColor;

void WinRect::init(int newBoxesX, int newBoxesY, int newBoxesWidth, int newBoxesHeight, std::string winRectFile) {
	boxesX = newBoxesX;
	boxesY = newBoxesY;
	boxesWidth = newBoxesWidth;	
	boxesHeight = newBoxesHeight;

	drawRect.x = Game::topLeftX + boxesX * Level::boxRect.w;
	drawRect.y = Game::topLeftY + boxesY * Level::boxRect.h;
	drawRect.w = boxesWidth * Level::boxRect.w;
	drawRect.h = boxesHeight * Level::boxRect.h;
	winDoorImage = loadTextureFromPNG(winRectFile);
	ratio = getTextureRatio(winDoorImage);


}



void WinRect::render() {

	SDL_RenderCopy(Window::renderer, winDoorImage, NULL, &drawRect);
	
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

WinRect::~WinRect() {
	SDL_DestroyTexture(winDoorImage);
}

void WinRect::setBoxesX(int x) {
	boxesX = x;
	resizeBox();
}

void WinRect::setBoxesY(int y) {
	boxesY = y;
	resizeBox();
}