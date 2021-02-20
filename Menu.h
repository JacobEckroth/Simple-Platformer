#pragma once
#include "Button.h"
#include <vector>
#include "SDL.h"


class Menu
{

public:
	void render();
	void resizeMenu();
	void init(int x,int y, bool newGrayedOut, bool horizontallyCentered,bool verticallyCentered, bool leftAligned,bool rightAligned,bool displayVertically, bool displayHorizontally, std::vector<Button*>);

	//returns the index of a pressed button.
	int checkForMousePress();
	void updateButtons();

	void setActive(bool newActive);
	bool getActive();
	//returns menu height of buttons and all buffers in between them.
	int getTotalMenuHeight(int buffer);
	int getTotalMenuWidth(int buffer);
	static SDL_Color grayColor;


	void updateButton(Button* button, int index);

	~Menu();
private:

	SDL_Rect grayOutRect;



	std::vector<Button*> buttons;

	int startingX;
	int startingY;
	bool displayHorizontally;
	bool displayVertically;

	
	bool verticallyCentered;	//true if it's vertically centered, if false starts from top.
	
	bool middleAligned;
	bool leftAligned;
	bool rightAligned;
	bool active;

	bool grayedOut;
	
};

