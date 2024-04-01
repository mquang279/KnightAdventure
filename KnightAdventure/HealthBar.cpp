#include "HealthBar.h"

HealthBar::HealthBar() {
	mWidth = 0;
	mHeight = 0;
	frame = 0;
}

HealthBar::~HealthBar() {

}

bool HealthBar::loadImage() {
	bool success = mHealthBar.loadFromFile("assets/health_bar/healthbar.png");
	if (success) {
		mWidth = mHealthBar.getWidth() / HEALTH_FRAMES;
		mHeight = mHealthBar.getHeight();

		for (int i = 0; i < HEALTH_FRAMES; i++) {
			mSpriteClips[i].x = i * mWidth;
			mSpriteClips[i].y = 0;
			mSpriteClips[i].w = mWidth;
			mSpriteClips[i].h = mHeight;
		}
	}
	return success;
}

void HealthBar::setSpriteFrame(int healthFrame) {
	frame = healthFrame;
}

void HealthBar::render() {
	mHealthBar.render(10, 10, &mSpriteClips[frame], NULL, NULL, SDL_FLIP_NONE);
}


