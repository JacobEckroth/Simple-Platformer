#pragma once
#include "RectanglePlatform.h"
#include <string>
#include <vector>
#define LEVEL_FOLDER "levels/"
class Level
{

public:
	
	void render();
	void loadFromFile(const char* fileName);
	void init(const char*);
	~Level();
	void handleRectPlatformLine(std::string, int);
	int getAmountOfPlatforms();
	void initializeStartingPosition(std::string);
	void initializeWinRect(std::string);
	std::vector<RectanglePlatform> getPlatforms();
	void drawWinRect();
	int getStartingY();
	int getStartingX();

	

	//stuff for creating a level down here:

	void addPlatform(RectanglePlatform);
	void setStartX(int);
	void setStartY(int);
	void setEndRect(SDL_Rect);
	 
	void writeLevelToFile(const char* fileName);

private:
	int playerStartX;
	int playerStartY;

	SDL_Rect winRect;
	std::vector<RectanglePlatform> platforms;

	bool levelLoaded;
};