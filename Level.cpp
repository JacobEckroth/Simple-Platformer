#include "Level.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>
#include <sstream>
#include "Window.h"
#include <SDL.h>
void Level::render() {
	for (int i = 0; i < platforms.size(); ++i) {
		platforms[i].render();
	}
	drawWinRect();
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
	levelLoaded = false;

	loadFromFile(fileName);
}

Level::~Level() {

}

int Level::getStartingY() {
	return playerStartY;
}

int Level::getStartingX() {
	return playerStartX;
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
	winRect.x = stoi(token);
	std::getline(iss, token, ' ');
	winRect.y = stoi(token);
	std::getline(iss, token, ' ');
	winRect.w = stoi(token);
	std::getline(iss, token, ' ');
	winRect.h = stoi(token);
}


void Level::drawWinRect() {
	SDL_SetRenderDrawColor(Window::renderer, 255, 215, 0, 255);
	SDL_RenderFillRect(Window::renderer, &winRect);
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

void Level::setEndRect(SDL_Rect newRect) {
	winRect.x = newRect.x;
	winRect.y = newRect.y;
	winRect.h = newRect.h;
	winRect.w = newRect.w;
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
	writeFile << std::to_string(winRect.x) << " " << std::to_string(winRect.y) << " " << std::to_string(winRect.w) << " " << std::to_string(winRect.h) << "\n";


	writeFile.close();

}

