#pragma once

#include "Game.h"
#include "LTexture.h"
#include "Map.h"


class Potion {
public:
	Potion();
	~Potion();
	void loadPotion(float x);
	void render(int mapX);
	void setPosY(Map& map_data, Map& trap_map, int mapX);
	SDL_Rect getPotionHitbox();
private:
	float posChange;
	float mVelY;
	SDL_Rect potionHitbox;
	float mPosX, mPosY;
	int mWidth, mHeight;
	LTexture healthPotion;
};