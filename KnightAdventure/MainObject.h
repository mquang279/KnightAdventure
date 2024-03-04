#pragma once
#include "Game.h"
#include "Map.h"
#include "LTexture.h"

const int ANIMATION_FRAMES = 8;
const int IDLE_FRAMES = 4;
const int TILE_SIZE = 32;
const float GRAVITY_SPEED = 0.8;
const float MAX_GRAVITY_SPEED = 10;

class MainObject : public LTexture {
public:
	MainObject();
	~MainObject();
	const static int POS_VEL = 5;
	enum WalkType {
		PLAYER_IDLE = -1,
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};
	bool loadImage(string path);
	void handleInput(SDL_Event& e);
	void move(Map& map_data);
	void render();
	void setSpriteClips();
private:
	int numberClips;
	SDL_RendererFlip flip;
	float mVelX, mVelY;
	float mPosX, mPosY;
	int mWidth, mHeight;
	SDL_Rect mSpriteClipsRun[ANIMATION_FRAMES];
	SDL_Rect mSpriteClipsIdle[IDLE_FRAMES];
	Input inputType;
	int frame;
	int playerStatus;
	LTexture mPlayerTexture;
	bool onGround;
};