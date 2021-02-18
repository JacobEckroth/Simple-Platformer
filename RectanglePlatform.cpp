#include "RectanglePlatform.h"
#include "Window.h"
#include <iostream>

void RectanglePlatform::init(int newX, int newY, int newWidth, int newHeight, SDL_Color newColor) {
	drawRect.x = hitbox.x = newX;
	drawRect.y = hitbox.y = newY;
	drawRect.w = hitbox.w = newWidth;
	drawRect.h = hitbox.h = newHeight;
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