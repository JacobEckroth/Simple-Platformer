#pragma once
#include <string>
#include "SDL.h"
SDL_Texture* loadTextureFromPNG(std::string fileName);


float getTextureRatio(SDL_Texture* texture);