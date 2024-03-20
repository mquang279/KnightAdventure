#pragma once

#include "Game.h"
#include "LTexture.h"
#include "Map.h"

const int ENEMY_FRAMES = 5;
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
	void move(Map& map_data);
	void render(int mapX);
	void setSpriteClips();
private:
	LTexture mEnemyTexture;
	bool onGround;
	float mPosX, mPosY, mVelX, mVelY;
	int frame;
	int mWidth, mHeight;
	SDL_Rect mSpriteClipsEnemy[ENEMY_FRAMES];
};