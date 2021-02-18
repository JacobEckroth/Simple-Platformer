#include "Game.h"
#include <iostream>
#include "SDL.h"
#include "Window.h"
#define GRAVITY 1000.
#define JUMPFORCE -600.
//#define JUMPFORCE -1500.

#define MOVEFORCE 2000.
#define GROUNDFRICTION .3
#define PADDING 1.

void Game::render() {
	player.render();
	level->render();
	if (drawingRect) {
		renderDrawRect();
	}
}

void Game::renderDrawRect() {
	SDL_Color defaultColor;
	defaultColor.r = defaultColor.g = defaultColor.b = 0;
	defaultColor.a = 255;
	SDL_SetRenderDrawColor(Window::renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
	SDL_RenderFillRect(Window::renderer, &drawRect);
}


void Game::update(float deltaTime) {
	updatePlayer(deltaTime);
	if (drawingRect) {
		updateDrawRectCoords();
	}
}

void Game::updateDrawRectCoords() {
	
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	
	drawRect.w = mouseX - drawRect.x;
	
	drawRect.h = mouseY - drawRect.y;
	


	
}

void Game::flipEditMode() {
	editingLevel = !editingLevel;
}


void Game::init(int w, int h) {
	gameScreenWidth = w;
	gameScreenHeight = h;
	SDL_Color playerColor;
	playerColor.r = 255;
	playerColor.g = 0;
	playerColor.b = 0;
	playerColor.a = 255;
	player.init(0, 0, 30, 50, playerColor );
	level = new Level();
	level->init("1.txt");
	player.setY(level->getStartingY());
	player.setX(level->getStartingX());
	editingLevel = false;
}

void Game::writeFile(const char* fileName) {
	level->writeLevelToFile(fileName);
}

void Game::updatePlayer(float deltaTime) {
	updatePlayerVertical(deltaTime);
	updatePlayerHorizontal(deltaTime);

}

void Game::updatePlayerVertical(float deltaTime) {
	if (player.isOnPlatform()) {
		SDL_Rect platform = player.getPlatform().getHitbox();
		if (!areRectsHorizontallyIntersecting(platform, player.getHitbox())) {
			
			player.setOnPlatform(false);
		}
	}

	if (!player.isOnGround() && !player.isOnPlatform()) {

		float y = player.getY();

	
		float yVel = player.getYVel() + GRAVITY * deltaTime;

		if (yVel > player.getMaxYVel()) {
			yVel = player.getMaxYVel();
		}
		y = y + yVel * deltaTime + .5 * GRAVITY * pow(deltaTime, 2);




		player.setY(y);
		player.setYVel(yVel);
		resolvePlayerVerticalCollisions();
	}
}

void Game::updatePlayerHorizontal(float deltaTime) {
	int direction = 0;
	if (player.getMovingRight()) {
		direction += 1;
	}
	else if (player.getMovingLeft()) {
		direction -= 1;
	}
	float x = player.getX();
	float xVel = player.getXVel();



	xVel += direction * MOVEFORCE * deltaTime;
	if (direction == 0 && player.isOnGround()) {
		xVel *= GROUNDFRICTION;
	}
	if (direction == 0 && player.isOnPlatform()) {
		xVel *= GROUNDFRICTION;
	}
	if (xVel >= 0) {
		if (xVel > player.getMaxXVel()) {
			xVel = player.getMaxXVel();
		}
	}
	else if (xVel < 0) {
		if (abs(xVel) > player.getMaxXVel()) {
			xVel = -player.getMaxXVel();
		}
	}
	if (direction == 0) {
		if (abs(xVel) < PADDING) {
			xVel = 0;
		}
	}
	
	x += xVel * deltaTime;


	player.setXVel(xVel);
	player.setX(x);
	resolvePlayerHorizontalCollisions();
	
}




bool Game::resolvePlayerVerticalCollisions() {
	if (player.isOnGround()) {
		return false;
	}
	float y = player.getY();
	if (y + player.getHeight() > gameScreenHeight) {	//if the player hit bottom of screen
		
		player.setOnGround(true);
		player.setY(gameScreenHeight - player.getHeight());
		return true;
	}
	if (player.getY() < 0) {
		player.setY(0);
		player.setYVel(0);
	}

	int amountOfPlatforms = level->getAmountOfPlatforms();
	std::vector<RectanglePlatform> platforms = level->getPlatforms();
	SDL_Rect playerRect = player.getHitbox();
	for (int i = 0; i < amountOfPlatforms; ++i) {
		SDL_Rect platformRect = platforms[i].getHitbox();
		if (areRectsIntersecting(playerRect, platformRect)) {		//could optimize to check for only vertical
			//if the player is jumping into a platform
				if (areRectsVerticallyIntersecting(playerRect, platformRect)) {
					if (player.getYVel() < 0) {
						player.setYVel(0);
						player.setY(platformRect.y + platformRect.h);
					}
					else {
						player.setYVel(0);
						player.setY(platformRect.y - player.getHeight());
						player.setOnPlatform(true);
						RectanglePlatform test = platforms.at(i);
						player.setPlatform(test);
					}
				}
		}

	}




	return false;
}

bool Game::resolvePlayerHorizontalCollisions() {
	int w = player.getWidth();
	int x = player.getX();
	if (x < 0) {
		player.setX(0);
		if (!player.getMovingRight()) {
			player.setXVel(0);
		}
		return true;
	}
	if (x + w >= gameScreenWidth) {
		player.setX(gameScreenWidth - w);
		if (!player.getMovingLeft()) {
			player.setXVel(0);
		}
		return true;
	}
	int amountOfPlatforms = level->getAmountOfPlatforms();
	std::vector<RectanglePlatform> platforms = level->getPlatforms();
	SDL_Rect playerRect = player.getHitbox();
	for (int i = 0; i < amountOfPlatforms; ++i) {
		SDL_Rect platformRect = platforms[i].getHitbox();
		if (areRectsIntersecting(playerRect, platformRect)) {		//could optimize to check for only vertical
			//if the player is jumping into a platform
			if (areRectsHorizontallyIntersecting(playerRect, platformRect)) {
				if (player.getXVel() > 0) {
					player.setXVel(0);
					player.setX(platformRect.x -player.getWidth());
				}
				else {
					player.setXVel(0);
					player.setX(platformRect.x + platformRect.w);
				
				}
			}
		}

	}
	return false;
}


void Game::attemptPlayerJump() {
	
	if (player.isOnGround() || player.isOnPlatform()) {
	
		player.setOnGround(false);
		player.setOnPlatform(false);
		player.setYVel(JUMPFORCE);
	}
}

void Game::attemptPlayerMoveLeft(bool moving) {
	player.setMovingLeft(moving);
}

void Game::attemptPlayerMoveRight(bool moving) {
	player.setMovingRight(moving);
}


bool Game::areRectsIntersecting(SDL_Rect rect1, SDL_Rect rect2) {
	// If one rectangle is on left side of other 
	if (rect1.x >= rect2.x + rect2.w || rect2.x >= rect1.x + rect1.w) {
		return false;	
	}
	if (rect1.y >= rect2.y + rect2.h || rect2.y >= rect1.y + rect1.h) {
		return false;
	}
	return true;
}


//we know they're intersecting, now we check if it's vertical or not.
bool Game::areRectsVerticallyIntersecting(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.y >= rect2.y + rect2.h || rect2.y >= rect1.y + rect1.h) {
		return false;
	}
	return true;

}

bool Game::areRectsHorizontallyIntersecting(SDL_Rect rect1, SDL_Rect rect2) {
	
	if (rect1.x >= rect2.x + rect2.w || rect2.x >= rect1.x + rect1.w) {
		
		return false;
	}
	return true;
}



void Game::handleMouseDown(SDL_MouseButtonEvent& b) {
	if (b.button == SDL_BUTTON_LEFT) {
		startDrawingRect();
	}
	
}

void Game::startDrawingRect() {
	drawingRect = true;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	drawRect.x = mouseX;
	drawRect.y = mouseY;
	drawRect.w = 0;
	drawRect.h = 0;
}

void Game::stopDrawingRect() {
	drawingRect = false;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX - drawRect.x <= 0) {
		drawRect.w = drawRect.x - mouseX;
		drawRect.x = mouseX;
		
	}
	else {
		drawRect.w = mouseX - drawRect.x;
	}
	
	if (mouseY - drawRect.y <= 0) {
		drawRect.h = drawRect.y - mouseY;
		drawRect.y = mouseY;
		
	}
	else {
		drawRect.h = mouseY - drawRect.y;
	}

	addDrawRectToLevel();
}

void Game::addDrawRectToLevel() {
	RectanglePlatform newPlatform;
	SDL_Color defaultColor;
	defaultColor.r = defaultColor.g = defaultColor.b = 0;
	defaultColor.a = 255;
	newPlatform.init(drawRect.x, drawRect.y, drawRect.w, drawRect.h, defaultColor);
	level->addPlatform(newPlatform);
}


void Game::handleMouseUp(SDL_MouseButtonEvent& b) {
	if (b.button == SDL_BUTTON_LEFT) {
		stopDrawingRect();
	}
	
}

void Game::updateWindowSize(int newWidth, int newHeight) {
	gameScreenHeight = newHeight;
	gameScreenWidth = newWidth;
}