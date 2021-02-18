#pragma once
#include "Player.h"
#include "Level.h"
class Game
{
private:
	Player player;
	int gameScreenWidth;		//will be a square.
	int gameScreenHeight;
	Level* level;

	bool editingLevel;

	bool drawingRect;
	SDL_Rect drawRect;
	

public:
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

	void updateWindowSize(int, int);
};

