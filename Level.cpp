#include "Level.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>
#include <sstream>
#include "Window.h"
#include <SDL.h>
#include "Game.h"

#define VERTICALBOXES 40
#define HORIZONTALBOXES 40


SDL_Rect Level::boxRect;
int Level::verticalBoxes;
int Level::horizontalBoxes;
void Level::render() {
	//drawBoxes();
	
	drawWindowRect();
	for (int i = 0; i < platforms.size(); ++i) {
		platforms[i].render();
	}
	winRect.render();
}

void Level::drawWindowRect() {
	SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(Window::renderer, &windowRect);
}


void Level::loadFromFile(const char* fileName) {
	std::ifstream levelFile;
	std::string line;
	std::string fileString = LEVEL_FOLDER;
	fileString += fileName;
	std::cout << "File name: " << fileString << std::endl;
	levelFile.open(fileString, std::ios::in);
	if (levelFile.is_open()) {
		getline(levelFile, line);
		int amountOfPlatforms = stoi(line);

		for (int i = 0; i < amountOfPlatforms; i++) {
			getline(levelFile, line);
			handleRectPlatformLine(line, i);
		}
		getline(levelFile, line);
		initializeStartingPosition(line);
		getline(levelFile, line);
		initializeWinRect(line);
	}
	else {
		fprintf(stderr, "Faiure opening levelFile %s , exiting\n", fileName); fflush(stderr);
		levelLoaded = false;
		return;
	}

}

void Level::init(const char* fileName) {

	//initializing win color.
	WinRect::winColor.r = 0;
	WinRect::winColor.g = 255;
	WinRect::winColor.b = 0;
	WinRect::winColor.a = 255;
	levelLoaded = false;
	boxRect.x = boxRect.y = 0;
	verticalBoxes = VERTICALBOXES;
	horizontalBoxes = HORIZONTALBOXES;
	boxRect.w = Game::gameScreenWidth / horizontalBoxes;
	boxRect.h = Game::gameScreenHeight / verticalBoxes;


	windowRect.w = boxRect.w * horizontalBoxes;
	windowRect.h = boxRect.h * verticalBoxes;
	windowRect.x = Game::topLeftX;
	windowRect.y = Game::topLeftY;


	loadFromFile(fileName);
}

void Level::drawBoxes() {
	SDL_Rect drawRect;
	drawRect.w = boxRect.w;
	drawRect.h = boxRect.h;
	SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
	for (int x = 0; x < horizontalBoxes; x++) {
		for (int y = 0; y < verticalBoxes; y++) {
			drawRect.x = Game::topLeftX + x * boxRect.w;
			drawRect.y =Game::topLeftY +  y * boxRect.h;
			SDL_RenderDrawRect(Window::renderer, &drawRect);
		}
	}


}




Level::~Level() {

}

int Level::getStartingY() {
	return playerStartY;
}

int Level::getStartingX() {
	return playerStartX;
}

void Level::updateBoxSize() {


	boxRect.w = Game::gameScreenWidth / horizontalBoxes;
	boxRect.h = Game::gameScreenHeight / verticalBoxes;
	for (int i = 0; i < platforms.size(); i++) {
		platforms.at(i).resizeBox();
	}
	windowRect.w = boxRect.w * horizontalBoxes;
	windowRect.h = boxRect.h * verticalBoxes;
	windowRect.x = Game::topLeftX;
	windowRect.y = Game::topLeftY;

	winRect.resizeBox();
}

void Level::handleRectPlatformLine(std::string line, int index) {
	
	std::istringstream iss(line);
	std::string token;

	std::getline(iss, token, ' ');
	int x = stoi(token);
	std::getline(iss, token, ' ');
	int y = stoi(token);
	std::getline(iss, token, ' ');
	int w = stoi(token);
	std::getline(iss, token, ' ');
	int h = stoi(token);
	std::getline(iss, token, ' ');
	int r = stoi(token);
	
	std::getline(iss, token, ' ');
	int g = stoi(token);
	std::getline(iss, token, ' ');
	int b = stoi(token);
	std::getline(iss, token, ' ');
	int a = stoi(token);

	SDL_Color newColor;
	newColor.r = r;
	newColor.g = g;
	newColor.b = b;
	newColor.a = a;
	
	
	RectanglePlatform platform;
	platform.init(x, y, w, h, newColor);
	platforms.push_back(platform);

}

std::vector<RectanglePlatform> Level::getPlatforms() {
	return platforms;
}

int Level::getAmountOfPlatforms() {
	return platforms.size();
}


void Level::initializeStartingPosition(std::string line) {

	std::istringstream iss(line);
	std::string token;

	std::getline(iss, token, ' ');
	playerStartX = stoi(token);
	std::getline(iss, token, ' ');
	playerStartY = stoi(token);
	
}
void Level::initializeWinRect(std::string line) {
	std::istringstream iss(line);
	std::string token;

	std::getline(iss, token, ' ');
	int x = stoi(token);
	std::getline(iss, token, ' ');
	int y = stoi(token);
	std::getline(iss, token, ' ');
	int w = stoi(token);
	std::getline(iss, token, ' ');
	int h  = stoi(token) ;

	std::getline(iss, token, ' ');
	
	std::string doorFile = Game::getImageFilePath(token);

	winRect.init(x, y, w, h,doorFile);
}

void Level::updateWinRectLocation(int boxesX, int boxesY) {
	if (boxesX +winRect.getBoxesWidth() > Level::horizontalBoxes || boxesX < 0 ||boxesY + winRect.getBoxesHeight() > Level::verticalBoxes || boxesY < 0) {

	}
	else {
		winRect.setBoxesX(boxesX);
		winRect.setBoxesY(boxesY);
	}
}




void Level::addPlatform(RectanglePlatform platform) {
	platforms.push_back(platform);
}

void Level::setStartX(int newX) {
	playerStartX = newX;
}

void Level::setStartY(int newY) {
	playerStartY = newY;
}



void Level::writeLevelToFile(const char* fileName) {
	std::ofstream writeFile;
	std::string fileString;
	fileString = LEVEL_FOLDER;
	fileString += fileName;

	writeFile.open(fileString);

	writeFile << platforms.size() << "\n";
	for (int i = 0; i < platforms.size(); i++) {
		SDL_Rect hitbox = platforms[i].getHitbox();
		SDL_Color color = platforms[i].getColor();
		
		writeFile << std::to_string(hitbox.x) << " " << std::to_string(hitbox.y) << " ";
		writeFile << std::to_string(hitbox.w) << " " << std::to_string(hitbox.h) << " ";
		writeFile << std::to_string(color.r) << " " << std::to_string(color.g) << " ";
		writeFile << std::to_string(color.b) << " " << std::to_string(color.a) << "\n";
	}
	writeFile << std::to_string(playerStartX) << " " << std::to_string(playerStartY) << "\n";
	writeFile << std::to_string(winRect.getBoxesX()) << " " << std::to_string(winRect.getBoxesY()) << " " << std::to_string(winRect.getBoxesWidth()) << " " << std::to_string(winRect.getBoxesHeight()) << "\n";


	writeFile.close();

}


void Level::deleteMouseRectangle() {

	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int i = platforms.size()-1; i >=0; --i) {
	
		if (platforms.at(i).mouseInPlatform(x, y)) {
		
			platforms.erase(platforms.begin() + i);
		}
	}
}
