#pragma once
#include "Game.h"
#include "Map.h"
#include "LTexture.h"

const int ANIMATION_FRAMES = 8;
const int ATTACK_FRAMES = 8;
const int JUMP_FRAMES = 4;
const int IDLE_FRAMES = 4;
const int TILE_SIZE = 32;
const float GRAVITY_SPEED = 0.8;
const float MAX_GRAVITY_SPEED = 10;
const float JUMP_VAL = 16;

class MainObject : public LTexture {
public:
	MainObject();
	const static int POS_VEL = 5;
	enum WalkType {
		PLAYER_IDLE = -1,
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		PLAYER_JUMP = 2,
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
private:
	int numberClips;
	SDL_RendererFlip flip;
	float mVelX, mVelY;
	float mPosX, mPosY;
	float mFixX, mFixY;
	float mPlayerHitBoxX, mPlayerHitBoxY, mPlayerHitBoxW, mPlayerHitBoxH;
	float mAttackHitBoxX, mAttackHitBoxY, mAttackHitBoxW, mAttackHitBoxH;
	int mWidth, mHeight;
	SDL_Rect mSpriteClipsRun[ANIMATION_FRAMES];
	SDL_Rect mSpriteClipsAttack[ATTACK_FRAMES];
	SDL_Rect playerHitBox;
	SDL_Rect attackHitBox;
	Input inputType;
	int frame;
	int playerStatus;
	LTexture mPlayerTexture;
	int mapX;
	bool onGround;
};