#include "TextureManager.h"
#include "SDL_image.h"
#include "Window.h"

SDL_Texture* loadTextureFromPNG(std::string fileName) {
	SDL_Surface* surface= IMG_Load(fileName.c_str());
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	SDL_FreeSurface(surface);
	return newTexture;
}


float getTextureRatio(SDL_Texture* texture) {
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	return (float(w) / h);
}