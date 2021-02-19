#pragma once
#include "RectanglePlatform.h"
#include <string>
#include <vector>
#define LEVEL_FOLDER "levels/"
#include "WinRect.h"
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

	int getStartingY();
	int getStartingX();

	

	//stuff for creating a level down here:

	void addPlatform(RectanglePlatform);
	void setStartX(int);
	void setStartY(int);
	
	 
	void writeLevelToFile(const char* fileName);

	void drawBoxes();
	void updateBoxSize();
	void drawWindowRect();
	static SDL_Rect boxRect;
	static int verticalBoxes;
	static int horizontalBoxes;
private:
	int playerStartX;
	int playerStartY;
	SDL_Rect windowRect;

	


	WinRect winRect;
	std::vector<RectanglePlatform> platforms;

	bool levelLoaded;
};
