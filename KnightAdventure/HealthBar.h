#pragma once

#include "Game.h"
#include "LTexture.h"

const int HEALTH_FRAMES = 8;

class HealthBar {
public:
	HealthBar();
	~HealthBar();
	bool loadImage();
	void render();
	void setSpriteFrame(int healthFrame);
private:
	LTexture mHealthBar;
	int mWidth, mHeight;
	int frame;
	SDL_Rect mSpriteClips[100];
};