#include "Game.h"
#include <iostream>
#include "SDL.h"
#include "Window.h"
#define GRAVITY 100.
#define JUMPFORCE -30.
//#define JUMPFORCE -1500.

#define MOVEFORCE 3.
#define GROUNDFRICTION .01
#define PADDING .2
int Game::topLeftX;
int Game::topLeftY;
int Game::gameScreenWidth;
int Game::gameScreenHeight;

void Game::render() {
	level->render();
	if (editingLevel) {
		if (drawingRect) {
			renderDrawRect();
		}
	}
	
	player.render();
	renderDebugInfo();
}

void Game::renderDebugInfo() {
	std::vector<char*> strings;


	int playerX = player.getX();
	std::string xPos = "Xpos: " + std::to_string(playerX);

	strings.push_back((char*)xPos.c_str());

	std::string yPos = "Ypos: " + std::to_string(int(player.getY()));
	strings.push_back((char*)yPos.c_str());

	std::string xVel = "Xvel: " + std::to_string(int(player.getXVel()));
	strings.push_back((char*)xVel.c_str());

	std::string yVel = "Yvel: " + std::to_string(int(player.getYVel()));
	strings.push_back((char*)yVel.c_str());
	

	debugger.renderStrings(strings);

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


void Game::flipEditMode() {
	editingLevel = !editingLevel;
}


void Game::init(int w, int h) {
	
	updateWindowSize(w, h);
	SDL_Color playerColor;
	playerColor.r = 255;
	playerColor.g = 0;
	playerColor.b = 0;
	playerColor.a = 255;
	player.setColor(playerColor);

	loadNewLevel("1.txt");

	editingLevel = false;
}


void Game::loadNewLevel(const char* levelName) {
	if (level) {
		delete level;
	}
	level = new Level();
	level->init(levelName);
	player.init(0, 0, 1, 2);
	player.setY(level->getStartingY());
	player.setX(level->getStartingX());
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

	
		float yVel = player.getYVel() + GRAVITY * deltaTime * Level::boxRect.h;

		if (yVel > player.getMaxYVel() * Level::boxRect.h) {
			yVel = player.getMaxYVel() * Level::boxRect.h;
		}
		y = y + yVel * deltaTime + .5 * GRAVITY * pow(deltaTime, 2) * Level::boxRect.h;




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



	xVel += direction * MOVEFORCE * deltaTime * Level::boxRect.w;
	if (direction == 0 && player.isOnGround()) {
		xVel *= GROUNDFRICTION;
	}
	if (direction == 0 && player.isOnPlatform()) {
		xVel *= GROUNDFRICTION;
	}
	if (xVel >= 0) {
		if (xVel > player.getMaxXVel()*Level::boxRect.w) {
			xVel = player.getMaxXVel()*Level::boxRect.w;
		}
	}
	else if (xVel < 0) {
		if (abs(xVel) > player.getMaxXVel()*Level::boxRect.w) {
			xVel = -player.getMaxXVel()*Level::boxRect.w;
		}
	}
	if (direction == 0) {
		if (abs(xVel) < PADDING) {
		
			xVel = 0;
		}
	}

	x += xVel * deltaTime * Level::boxRect.w;

	
	player.setXVel(xVel);
	player.setX(x);
	resolvePlayerHorizontalCollisions();
	
}




bool Game::resolvePlayerVerticalCollisions() {
	if (player.isOnGround()) {
		return false;
	}
	float y = player.getY();
	if (y + player.getHeight() > Game::topLeftY +  Level::boxRect.h * Level::verticalBoxes) {	//if the player hit bottom of screen
		
		player.setOnGround(true);
		player.setY(Game::topLeftY + Level::boxRect.h * Level::verticalBoxes - player.getHeight());
		return true;
	}
	if (player.getY() < 0) {
		player.setY(Game::topLeftY);
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
		player.setX(topLeftX);
		if (!player.getMovingRight()) {
			player.setXVel(0);
		}
		return true;
	}
	if (x + w >= Game::topLeftX + Level::boxRect.w * Level::horizontalBoxes) {
		player.setX(Game::topLeftX + Level::boxRect.w * Level::horizontalBoxes - w);
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
		player.setYVel(JUMPFORCE * Level::boxRect.h);
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
	if (editingLevel) {
		if (b.button == SDL_BUTTON_LEFT) {
			startDrawingRect();
		}
	}
	
	
}


void Game::updateDrawRectCoords() {

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);


	drawRect.w = (int((abs(mouseX - drawRect.x))/Level::boxRect.w) + 1) * Level::boxRect.w ;

	drawRect.h = (int((abs(mouseY - drawRect.y)) / Level::boxRect.h) + 1) * Level::boxRect.h;

	if (mouseX - drawRect.x < 0) {
		if (!drawNegX) {
			drawNegX = true;
			drawRect.x += Level::boxRect.w;
		}
		drawRect.w = -drawRect.w;
	}
	else {
		//if we're switching back to positive x, i.e. mouse is to right of rect x y
		if (drawNegX) {
			drawNegX = false;
			drawRect.x -= Level::boxRect.w;
		}
	}
	if (mouseY - drawRect.y < 0) {
		drawRect.h = -drawRect.h;
		if (!drawNegY) {
			drawNegY = true;
			drawRect.y += Level::boxRect.h;
		}
	}
	else {
		//switching back to positive y
		if (drawNegY) {
			drawNegY = false;
			drawRect.y -= Level::boxRect.h;
		}
	}

}



void Game::startDrawingRect() {
	drawNegX = drawNegY = false;
	drawingRect = true;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	drawRect.x = Game::topLeftX + int((mouseX-Game::topLeftX) / Level::boxRect.w) * Level::boxRect.w;
	drawRect.y = Game::topLeftY + int((mouseY-Game::topLeftY) / Level::boxRect.h) * Level::boxRect.h;
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
	float boxesX = (drawRect.x-Game::topLeftX) / Level::boxRect.w;
	float boxesY = (drawRect.y-Game::topLeftY) / Level::boxRect.h;
	
	int roundedBoxesX, roundedBoxesY, roundedBoxesW, roundedBoxesH;

	roundedBoxesX = int(boxesX);
	
	
	roundedBoxesY = int(boxesY);

	float boxesEndX = int(drawRect.x + drawRect.w - Game::topLeftX) / Level::boxRect.w;

	float boxesEndY = int(drawRect.y + drawRect.h - Game::topLeftY) / Level::boxRect.h;

	
	//funky stuff happens if we don't do this I have no idea why
	if (drawNegX) {
		roundedBoxesW = int(boxesEndX - boxesX);
	}
	else {
		roundedBoxesW = int(boxesEndX - boxesX) + 1;
	}
	if (drawNegY) {
		roundedBoxesH = int(boxesEndY - boxesY);
	}
	else {
		roundedBoxesH = int(boxesEndY - boxesY) + 1;
	}
	
	
	
	
	

	if (roundedBoxesX + roundedBoxesW > Level::horizontalBoxes || roundedBoxesX < 0 || roundedBoxesY +roundedBoxesH> Level::verticalBoxes || roundedBoxesY < 0) {
		//out of bounds
	}
	else {
		if (roundedBoxesH != 0 && roundedBoxesW != 0) {
			newPlatform.init(roundedBoxesX, roundedBoxesY, roundedBoxesW, roundedBoxesH, defaultColor);
			level->addPlatform(newPlatform);
		}
	}

	
}


void Game::handleMouseUp(SDL_MouseButtonEvent& b) {
	if (editingLevel) {
		if (b.button == SDL_BUTTON_LEFT) {
			stopDrawingRect();
		}
	}
	
	
}

void Game::updateWindowSize(int newWidth, int newHeight) {
	if (newHeight > newWidth) {
		gameScreenHeight = newWidth;
		gameScreenWidth = newWidth;
	}
	else {
		gameScreenHeight = newHeight;
		gameScreenWidth = newHeight;
	}

	topLeftX = (newWidth - gameScreenWidth) / 2;
	topLeftY = (newHeight - gameScreenHeight) / 2;

}


void Game::updateSizes(int newW, int newH) {
	updateWindowSize(newW, newH);
	level->updateBoxSize();
	player.resizePlayer();
}