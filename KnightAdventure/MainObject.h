#pragma once
#include "Game.h"
#include "Map.h"
#include "LTexture.h"

const int ANIMATION_FRAMES = 8;
const int TOTAL_ANIMATION = 4;
const int TILE_SIZE = 32;
const float GRAVITY_SPEED = 0.85;
const float MAX_GRAVITY_SPEED = 10;
const float JUMP_VAL = 16;

class MainObject : public LTexture {
public:
	MainObject();
	const static int POS_VEL = 5;
	enum WalkType {
		PLAYER_IDLE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		PLAYER_ATTACK = 3,
	};
	bool loadImage(string path);
	void handleInput(SDL_Event& e);
	void move(Map& map_data);
	void render();
	void setSpriteClips();
	void setWidthHeight();
	int getMapX();
	void centerEntityOnMap();
	float getPosX();
	float getPosY();
	SDL_Rect getPlayerHitbox();
	SDL_Rect getPlayerAttackHitbox();
	int getPlayerStatus();
	int getPlayerCurrentFrame();
	int getAttackTime();
	void renderDeadFrame();
private:
	bool dieFinish;
	int numberClips;
	SDL_RendererFlip flip;
	float mVelX, mVelY;
	float mPosX, mPosY;
	float mFixX, mFixY;
	float mPlayerHitBoxX, mPlayerHitBoxY, mPlayerHitBoxW, mPlayerHitBoxH;
	float mAttackHitBoxX, mAttackHitBoxY, mAttackHitBoxW, mAttackHitBoxH;
	int mWidth, mHeight;
	int mDeadWidth, mDeadHeight;
	SDL_Rect mSpriteClips[TOTAL_ANIMATION][ANIMATION_FRAMES];
	SDL_Rect playerHitBox;
	SDL_Rect attackHitBox;
	Input inputType;
	int frame;
	int playerStatus;
	LTexture mPlayerTexture;
	int mapX;
	bool onGround;
	bool attackAnimationFinished;
	int attackAnimationTime;
	int dieFrame;
};