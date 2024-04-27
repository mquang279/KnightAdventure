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
	bool loadDeathImage(string path);
	void setVelX(const float& xVal) { mVelX = xVal; };
	void setVelY(const float& yVal) { mVelY = yVal; };
	void setPosX(const float& xPos) { mPosX = xPos; };
	void setPosY(const float& yPos) { mPosY = yPos; };
	float getPosX() { return mPosX; };
	float getPosY() { return mPosY; };
	int getWidth();
	int getHeight();
	void setEnemyFrames(int randomNum);
	void move(Map& map_data, Map& trap_map);
	void render(int mapX, bool pauseGame);
	void renderDieFrame(int mapX);
	void setSpriteClips();
	bool getTrapHit();
	SDL_Rect getEnemyHitbox();
private:
	int ENEMY_DIE_FRAMES;
	LTexture mEnemyTexture;
	LTexture mEnemyDie;
	bool onGround;
	int ENEMY_FRAMES;
	float mPosX, mPosY, mVelX, mVelY;
	int frame;
	int dieFrame;
	int mWidth, mHeight;
	int mDieWidth, mDieHeight;
	bool dieFinish;
	bool trapHit;
	SDL_RendererFlip flip;
	SDL_Rect mEnemyHitBox;
	SDL_Rect mSpriteClipsEnemy[100];
	SDL_Rect mSpriteClipsEnemyDie[7];
};