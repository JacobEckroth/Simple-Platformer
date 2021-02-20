#include "Menu.h"
#include "Window.h"
#include <iostream>
SDL_Color Menu::grayColor = { 122,122,122,122 };

void Menu::render() {
	if (active) {

		if (grayedOut) {
			SDL_SetRenderDrawColor(Window::renderer, grayColor.r, grayColor.g, grayColor.b, grayColor.a);
			SDL_RenderFillRect(Window::renderer, &grayOutRect);
		}


		for (int i = 0; i < buttons.size(); i++) {

			buttons.at(i)->render();
		}
	}

}

//this works don't you dare fucking touch it. The only thing to change
//would be adding buffers in case the menus go off the screen.
//but you could just design it so that's impossible. good plan jacob.
void Menu::resizeMenu() {
	int verticalBuffer = Level::boxRect.h;
	int horizontalBuffer = Level::boxRect.w;


	for (int i = 0; i < buttons.size(); i++) {
		buttons.at(i)->updateButtonSize();
	}
	int totalHeight = getTotalMenuHeight(verticalBuffer);
	int totalWidth = getTotalMenuWidth(horizontalBuffer);
	int middleOfScreenX = Window::screenWidth / 2;
	int middleOfScreenY = Window::screenHeight / 2;
	if (displayVertically) {
		if (middleAligned) {
		
			if (verticallyCentered) {

				int currentYPos = (Window::screenHeight - totalHeight) / 2;

				for (int i = 0; i < buttons.size(); i++) {
					//if it extends past bottom of screen.

					buttons.at(i)->setX(middleOfScreenX - (buttons.at(i)->getWidth() / 2));
					buttons.at(i)->setY(currentYPos);
					currentYPos += buttons.at(i)->getHeight();
					currentYPos += verticalBuffer;
				}

			}
			else {
				//otherwise we just start at the top
				int currentYPos = verticalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(middleOfScreenX - (buttons.at(i)->getWidth() / 2));
					buttons.at(i)->setY(currentYPos);
					currentYPos += buttons.at(i)->getHeight();
					currentYPos += verticalBuffer;
				}
			}
		}	//otherwise if it's not horizontally centered.
		else if (leftAligned) {
			if (verticallyCentered) {
				int currentYPos = (Window::screenHeight - totalHeight) / 2;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(horizontalBuffer);
					buttons.at(i)->setY(currentYPos);
					currentYPos += buttons.at(i)->getHeight();
					currentYPos += verticalBuffer;
				}
			}
			else {
				int currentYPos = verticalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(horizontalBuffer);
					buttons.at(i)->setY(currentYPos);
					currentYPos += buttons.at(i)->getHeight();
					currentYPos += verticalBuffer;
				}
			}

		}
		else if (rightAligned) {
			if (verticallyCentered) {
				int currentYPos = (Window::screenHeight - totalHeight) / 2;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(Window::screenWidth - buttons.at(i)->getWidth() - horizontalBuffer);
					buttons.at(i)->setY(currentYPos);
					currentYPos += buttons.at(i)->getHeight();
					currentYPos += verticalBuffer;
				}
			}
			else {
				int currentYPos = verticalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(Window::screenWidth - buttons.at(i)->getWidth() - horizontalBuffer);
					buttons.at(i)->setY(currentYPos);
					currentYPos += buttons.at(i)->getHeight();
					currentYPos += verticalBuffer;
				}
			}
		}
	}
	else if (displayHorizontally) {

		if (middleAligned) {
			
			if (verticallyCentered) {

				
				int currentXPos = (Window::screenWidth - totalWidth) / 2;
				for (int i = 0; i < buttons.size(); i++) {
					//if it extends past bottom of screen.

					buttons.at(i)->setX(currentXPos);
					buttons.at(i)->setY(Window::screenHeight/2 - buttons.at(i)->getHeight() / 2);
					currentXPos += buttons.at(i)->getWidth();
					currentXPos += horizontalBuffer;
				}

			}
			else {
				//otherwise we just start at the top
				
				int currentXPos = (Window::screenWidth - totalWidth) / 2;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(currentXPos);
					buttons.at(i)->setY(verticalBuffer);
					currentXPos += buttons.at(i)->getWidth();
					currentXPos += horizontalBuffer;
				}
			}
		}	//otherwise if it's not horizontally centered.
		else if (leftAligned) {
			if (verticallyCentered) {
				
				int currentXPos = horizontalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(currentXPos);
					buttons.at(i)->setY((middleOfScreenY - buttons.at(i)->getHeight()/2));
					currentXPos += buttons.at(i)->getWidth();
					currentXPos += horizontalBuffer;
				}
			}
			else {
				int currentXPos = horizontalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(currentXPos);
					buttons.at(i)->setY(verticalBuffer);
					currentXPos += buttons.at(i)->getWidth();
					currentXPos += horizontalBuffer;
				}
			}

		}
		else if (rightAligned) {
			if (verticallyCentered) {
				int currentXPos = Window::screenWidth - getTotalMenuWidth(horizontalBuffer) - horizontalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(currentXPos);
					buttons.at(i)->setY(middleOfScreenY - buttons.at(i)->getHeight() / 2);
					currentXPos += buttons.at(i)->getWidth();
					currentXPos += horizontalBuffer;
				}
			}
			else {
				int currentXPos = Window::screenWidth - getTotalMenuWidth(horizontalBuffer) - horizontalBuffer;
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->setX(currentXPos);
					buttons.at(i)->setY(verticalBuffer);
					currentXPos += buttons.at(i)->getWidth();
					currentXPos += horizontalBuffer;
				}
			}
		}
	}


}

int Menu::getTotalMenuHeight(int verticalBuffer) {
	int totalHeight = 0;

	//getting the total height to figure out where to start drawing the menu.
	for (int i = 0; i < buttons.size(); i++) {
		totalHeight += buttons.at(i)->getHeight();
		if (i != buttons.size() - 1) {
			totalHeight += verticalBuffer;
		}

	}
	return totalHeight;
}

int Menu::getTotalMenuWidth(int horizontalBuffer) {
	int totalWidth = 0;

	//getting the total height to figure out where to start drawing the menu.
	for (int i = 0; i < buttons.size(); i++) {
		totalWidth += buttons.at(i)->getWidth();
		if (i != buttons.size() - 1) {
			totalWidth += horizontalBuffer;
		}

	}
	return totalWidth;
}


void Menu::updateButtons() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons.at(i)->mouseInButton(x, y)) {
			buttons.at(i)->updateButtonActive(true);
		}
		else {
			buttons.at(i)->updateButtonActive(false);
		}
	}
}



void Menu::init(int newX, int newY, bool newGrayedOut, bool newVerticallyCentered, bool newMiddleAligned, bool newLeftAligned, bool newRightAligned, bool newDisplayVertically, bool newDisplayHorizontally, std::vector<Button*> newButtons) {
	startingX = newX;
	startingY = newY;
	
	leftAligned = newLeftAligned;
	rightAligned = newRightAligned;
	buttons = newButtons;
	middleAligned = newMiddleAligned;
	verticallyCentered = newVerticallyCentered;
	displayVertically = newDisplayVertically;
	displayHorizontally = newDisplayHorizontally;
	grayOutRect.x = 0;
	grayOutRect.y = 0;
	grayOutRect.w = Window::screenWidth;
	grayOutRect.h = Window::screenHeight;
	grayedOut = newGrayedOut;
	int buffer = Level::boxRect.h;	//buffer between buttons/top and bottom of screen.


	resizeMenu();

	active = false;


}


Menu::~Menu() {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons.at(i)) {
			delete buttons.at(i);
		}

	}
}


void Menu::setActive(bool newActive) {
	active = newActive;
}

bool Menu::getActive() {
	return active;
}

int Menu::checkForMousePress() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons.at(i)->mouseInButton(x,y)) {
			return i;
		}
	}
	return -1;
}

void Menu::updateButton(Button* button, int index) {
	Button* removeButton = buttons.at(index);
	if (removeButton) {
		delete removeButton;
	}

	buttons.erase(buttons.begin() + index);
	buttons.insert(buttons.begin() + index, button);
	resizeMenu();
}


