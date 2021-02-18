#include "Player.h"
#include "Window.h"
#include <iostream>

void Player::render() {
	SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Window::renderer, &drawRect);
}

void Player::init(int boxesX, int boxesY, int boxesW, int boxesH, SDL_Color newColor) {

	this->boxesW = boxesW;
	this->boxesH = boxesH;
	this->boxesX = boxesX;
	this->boxesY = boxesY;
	drawRect.w = Level::boxRect.w * boxesW;
	drawRect.h = Level::boxRect.h * boxesH;
	drawRect.x = Game::topLeftX + Level::boxRect.w * boxesX;
	drawRect.y = Game::topLeftY + Level::boxRect.h * boxesY;
	color.r = newColor.r;
	color.g = newColor.g;
	color.b = newColor.b;
	color.a = newColor.a;
	movement.xVel = 0;
	movement.yVel = 0;
	movement.mass = 10;
	movement.maxYVel = 1000;
	movement.maxXVel = .4;
	movingLeft = false;
	movingRight = false;
	onGround = false;
	onPlatform = false;
	
}

MovementInfo Player::getMovementInfo() {
	return movement;
}

void Player::setMovement(MovementInfo newMovement) {
	movement.xVel = newMovement.xVel;
	movement.yVel = newMovement.yVel;
}

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::setY(float newY) {
	drawRect.y = newY;
	y = newY;
	boxesY = (float(newY) - Game::topLeftY) / Level::boxRect.h;

}
void Player::setX(int newX) {
	x = newX;
	drawRect.x = newX;
	boxesX = float(newX - Game::topLeftX) / Level::boxRect.w;
	
}

void Player::resizePlayer() {
	drawRect.w = Level::boxRect.w * boxesW;
	drawRect.h = Level::boxRect.h * boxesH;
	drawRect.x = Game::topLeftX + boxesX * Level::boxRect.w;
	drawRect.y = Game::topLeftY + boxesY * Level::boxRect.h;
	x = drawRect.x;
	y = drawRect.y;
}


float Player::getYVel() {
	return movement.yVel;
}
void Player::setYVel(float newYVel) {
	movement.yVel = newYVel;
}

float Player::getMaxYVel() {
	return movement.maxYVel;
}

bool Player::isOnGround() {
	return onGround;
}

void Player::setOnGround(bool newOnGround) {
	onGround = newOnGround;
	if (onGround) {
		movement.yVel = 0;
	}
}

int Player::getHeight() {
	return drawRect.h;
}


float Player::getXVel() {
	return movement.xVel;
}

void Player::setXVel(float newXVel) {
	movement.xVel = newXVel;
}
float Player::getMaxXVel() {
	return movement.maxXVel;
}


bool Player::getMovingLeft() {
	return movingLeft;
}

bool Player::getMovingRight() {
	return movingRight;
}

void Player::setMovingLeft(bool newSet) {
	movingLeft = newSet;
}

void Player::setMovingRight(bool newSet) {
	movingRight = newSet;
}

int Player::getWidth() {
	return drawRect.w;
}

SDL_Rect Player::getHitbox() {
	return drawRect;
}


bool Player::isOnPlatform() {
	return onPlatform;
}

void Player::setPlatform(RectanglePlatform Platform) {
	platform = Platform;
}

void Player::setOnPlatform(bool newSet) {
	onPlatform = newSet;
}

RectanglePlatform Player::getPlatform() {
	return platform;
}