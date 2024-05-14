#pragma once

#include "Game.h"
#include "Map.h"
#include "LTexture.h"

const int ANIMATION_FRAMES = 8;
const int TOTAL_ANIMATION = 4;
const int TILE_SIZE = 32;
const float GRAVITY_SPEED = 0.85;
const float MAX_GRAVITY_SPEED = 15;
const float JUMP_VAL = 16;
const float POS_VEL = 4.5;
const int BUFF_FRAME = 16;

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

class MainObject : public LTexture {
public:
	MainObject();
	enum WalkType {
		PLAYER_IDLE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		PLAYER_ATTACK = 3,
		PLAYER_JUMP = 4,
	};
	bool loadImage(string path);
	void handleInput(SDL_Event& e);
	void move(Map& map_data);
	void render();
	void setSpriteClips();
	void setWidthHeight();
	void renderBuffEffect();
	int getMapX();
	void centerEntityOnMap();
	int getPosX();
	int getPosY();
	SDL_Rect getPlayerHitbox();
	SDL_Rect getPlayerAttackHitbox();
	int getPlayerStatus();
	int getPlayerCurrentFrame();
	int getAttackTime();
	void renderDeadFrame();
	void setPosX(int x);
	void setPosY(int y);
	bool getDeadStatus();
	void reload();
	bool getOnGroundStatus();
	void renderIdleFrame();
	bool getBuffFinish();
	void setBuffFinish(bool status);
private:
	SDL_RendererFlip flip;
	float mVelX, mVelY;
	float mPosX, mPosY;
	float mFixX, mFixY;
	float mPlayerHitBoxX, mPlayerHitBoxY, mPlayerHitBoxW, mPlayerHitBoxH;
	float mAttackHitBoxX, mAttackHitBoxY, mAttackHitBoxW, mAttackHitBoxH;
	int mWidth, mHeight;
	int mDeadWidth, mDeadHeight;
	SDL_Rect mSpriteClips[TOTAL_ANIMATION][ANIMATION_FRAMES];
	SDL_Rect mSpriteClipsBuff[BUFF_FRAME];
	SDL_Rect playerHitBox;
	SDL_Rect attackHitBox;
	Input inputType;
	int frame;
	int playerStatus;
	LTexture mPlayerTexture;
	LTexture mBuffTexture;
	int mapX;
	bool onGround;
	bool attackAnimationFinished;
	int attackAnimationTime;
	int dieFrame;
	bool isDead;
	bool buffFinish;
	int buffFrame;
};