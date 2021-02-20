#pragma once
#include "Player.h"
#include "Level.h"
#include "Debugger.h"
#include "Button.h"
#include "Menu.h"
class Game
{
private:
	Player player;
	
	Level* level;

	bool editingLevel;

	bool drawingRect;
	bool deleting;
	bool placingStart;
	bool placingWin;

	SDL_Color drawRectColor;
	SDL_Rect drawRect;
	bool drawNegX;
	bool drawNegY;
	Debugger debugger;




	Menu editButtonMenu;
	Menu editMenu;

public:
	static int gameScreenWidth;		//will be a square.
	static int gameScreenHeight;
	static int topLeftX;
	static int topLeftY;
	void render();
	void update(float);
	void init(int w, int h);
	void updatePlayer(float deltaTime);
	void updatePlayerVertical(float deltaTime);
	void updatePlayerHorizontal(float deltaTime);
	bool resolvePlayerVerticalCollisions();
	bool resolvePlayerHorizontalCollisions();

	bool areRectsIntersecting(SDL_Rect, SDL_Rect);
	bool areRectsVerticallyIntersecting(SDL_Rect, SDL_Rect);
	bool areRectsHorizontallyIntersecting(SDL_Rect, SDL_Rect);

	void attemptPlayerJump();
	void attemptPlayerMoveLeft(bool);
	void attemptPlayerMoveRight(bool);

	void flipEditMode();

	void writeFile(const char* fileName);



	void handleMouseDown(SDL_MouseButtonEvent& b);
	void handleMouseUp(SDL_MouseButtonEvent& b);


	void startDrawingRect();
	void stopDrawingRect();
	void addDrawRectToLevel();
	void updateDrawRectCoords();
	void renderDrawRect();

	void renderMenus();

	void updateSizes(int, int);
	void updateWindowSize(int, int);


	void loadNewLevel(const char* levelName);

	void renderDebugInfo();

	void initializeMenus();


	void updateMenus();
	void resizeMenus();
	std::string getImageFilePath(std::string imageName);

	bool handleMenuClick();



	//showing edit menu stuff
	void showEditMenu();
	void hideEditMenu();


	void toggleDeleteMode();
	void startPlacingStart();
	void startPlacingWin();
	

};

