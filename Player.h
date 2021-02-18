#pragma once
#include "SDL.h"
#include "MovementInfo.h"
#include "RectanglePlatform.h"
class Player
{


public:
	void render();
	void init(int, int, int, int, SDL_Color);
	MovementInfo getMovementInfo();
	void setMovement(MovementInfo);
	float getY();
	float getX();
	void setX(int);
	void setY(float);
	int getHeight();
	int getWidth();

	float getYVel();
	void setYVel(float);
	float getMaxYVel();

	float getXVel();
	void setXVel(float);
	float getMaxXVel();



	bool isOnGround();
	void setOnGround(bool);
	bool isOnPlatform();
	void setOnPlatform(bool);
	RectanglePlatform getPlatform();
	void setPlatform(RectanglePlatform);

	bool getMovingLeft();
	bool getMovingRight();
	void setMovingLeft(bool);
	void setMovingRight(bool);
	
	SDL_Rect getHitbox();

private:
	SDL_Rect drawRect;	//drawRectg and hitbox are the same

	SDL_Color color;
	MovementInfo movement;
	bool onGround;
	float y;
	float x;
	bool movingLeft;
	bool movingRight;
	bool onPlatform;
	RectanglePlatform platform;


};

