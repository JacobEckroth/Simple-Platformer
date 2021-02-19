#pragma once
#include "SDL_ttf.h"
#include <vector>
class Debugger
{
public:
	Debugger();
	~Debugger();
	void render();
	void renderStrings(std::vector<char*>);
private:
	TTF_Font* font;


};

