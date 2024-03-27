#pragma once

#include "Game.h"
#include "LTexture.h"
#include "Map.h"

const float ENEMY_GRAVITY_SPEED = 0.8;
const float ENEMY_MAX_GRAVITY_SPEED = 10;

class Enemy{
public:
	Enemy();
	~Enemy();
	bool loadImage(string path);
	void setVelX(const float& xVal) { mVelX = xVal; };
	void setVelY(const float& yVal) { mVelY = yVal; };
	void setPosX(const float& xPos) { mPosX = xPos; };
	void setPosY(const float& yPos) { mPosY = yPos; };
	float getPosX() { return mPosX; };
	float getPosY() { return mPosY; };
	int getWidth();
	int getHeight();
	void setEnemyFrames(int randomNum);
	void move(Map& map_data);
	void render(int mapX);
	void setEnemyHitBox(int randomNum);
	void setSpriteClips();
private:
	LTexture mEnemyTexture;
	bool onGround;
	int ENEMY_FRAMES;
	float mPosX, mPosY, mVelX, mVelY;
	int frame;
	int mWidth, mHeight;
	SDL_Rect mEnemyHitBox;
	SDL_Rect mSpriteClipsEnemy[100];
};