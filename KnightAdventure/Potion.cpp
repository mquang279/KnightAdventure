#include "Potion.h"

Potion::Potion() {
	mPosY = 0;
	mPosX = 0;
	mWidth = 0;
	mHeight = 0;
	mVelY = 0;
	posChange = 0.25;
	potionHitbox = { 0,0,0,0 };
}

Potion::~Potion() {

}

void Potion::loadPotion(float x) {
	healthPotion.loadFromFile("assets/health_bar/potion.png");
	mWidth = healthPotion.getWidth();
	mHeight = healthPotion.getHeight();
	mPosX = x;
}

void Potion::setPosY(Map& map_data, Map& trap_map, int mapX) {
	for (int i = 1; i < 640 / 32; i++) {
		if (map_data.map[i][(int)mPosX / 32] != 1 && trap_map.map[i - 1][(int)mPosX / 32] == 1) {
			mPosY = i * 32 - mHeight - 10;
			break;
		}
		else mPosY = 900;
	}
}

void Potion::render(int mapX) {
	mVelY += posChange;
	mPosY += posChange;
	if (mVelY >= 10 || mVelY <= -10) {
		posChange *= -1;
		mVelY = 0;
	}
	potionHitbox = { (int)mPosX - mapX, (int)mPosY + (int)posChange, mWidth, mHeight };
	healthPotion.render(mPosX - mapX, mPosY);
}

SDL_Rect Potion::getPotionHitbox() {
	return potionHitbox;
}