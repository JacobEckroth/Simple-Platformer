#include "Debugger.h"
#include "Window.h"


Debugger::Debugger() {
	TTF_Init();
	font = TTF_OpenFont("data/fonts/Montserrat-Regular.ttf", 25);
}



Debugger::~Debugger() {
	TTF_CloseFont(font);
	TTF_Quit();
}
void Debugger::render() {

}


void Debugger::renderStrings(std::vector<char*> strings) {
	int yPos = 0;
	SDL_Color color = { 255, 255, 255 };
	for (int i = 0; i < strings.size(); i++) {
		SDL_Surface* surface = TTF_RenderText_Solid(font,
			strings.at(i), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { 0, yPos, texW, texH };
		SDL_RenderCopy(Window::renderer, texture, NULL, &dstrect);
		yPos += texH;
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}




}