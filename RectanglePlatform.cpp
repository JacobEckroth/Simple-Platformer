#include "RectanglePlatform.h"
#include "Window.h"
#include <iostream>
#include "Level.h"
#include "Game.h"
void RectanglePlatform::init(int newX, int newY, int newWidth, int newHeight, SDL_Color newColor) {
	boxesX = newX;
	boxesY =  newY;
	boxesWidth = newWidth;
	boxesHeight = newHeight;
	drawRect.x = hitbox.x = Game::topLeftX + Level::boxRect.w* boxesX;
	drawRect.y = hitbox.y =Game::topLeftY + Level::boxRect.h * boxesY;
	drawRect.w = hitbox.w = Level::boxRect.w * boxesWidth;
	drawRect.h = hitbox.h = Level::boxRect.h * boxesHeight;
	color.r = newColor.r;
	color.g = newColor.g;
	color.b = newColor.b;
	color.a = newColor.a;
	
}


void RectanglePlatform::render() {
	SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Window::renderer, &drawRect);
}

SDL_Rect RectanglePlatform::getHitbox() {
	return hitbox;
}

SDL_Color RectanglePlatform::getColor() {
	return color;
}


void RectanglePlatform::resizeBox() {
	drawRect.w = hitbox.w =  Level::boxRect.w* boxesWidth;
	drawRect.h = hitbox.h = Level::boxRect.h * boxesHeight;
	drawRect.x = hitbox.x = Game::topLeftX + boxesX * Level::boxRect.w;
	drawRect.y = hitbox.y = Game::topLeftY + boxesY * Level::boxRect.h;

}