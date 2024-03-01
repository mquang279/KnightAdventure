#pragma once
#include "Game.h"
#include "LTexture.h"

const int ANIMATION_FRAMES = 8;

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
	void move();
	void render();
	void setSpriteClips();
private:
	int numberClips;
	SDL_RendererFlip flip;
	int mVelX, mVelY;
	int mPosX, mPosY;
	int mWidth, mHeight;
	SDL_Rect mSpriteClips[ANIMATION_FRAMES];
	Input inputType;
	int frame;
	int playerStatus;
	LTexture mPlayerTexture;
};