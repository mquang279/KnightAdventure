#include "MainObject.h"

MainObject::MainObject() {
	mVelX = 0;
	mVelY = 0;
	mPosX = 0;
	mPosY = 0;
	frame = 0;
	mWidth = 0;
	mHeight = 0;
	playerStatus = -1;
	flip = SDL_FLIP_NONE;
}

MainObject::~MainObject(){}

bool MainObject::loadImage(string path) {
	bool success = mPlayerTexture.loadFromFile(path.c_str());
	if (success) {
		mWidth = mPlayerTexture.getWidth() / ANIMATION_FRAMES;
		mHeight = mPlayerTexture.getHeight();
	}
	return success;
}

void MainObject::setSpriteClips() {
	if (mWidth > 0 && mHeight > 0) {
		for (int i = 0; i < ANIMATION_FRAMES; i++) {
			mSpriteClips[i].x = i * mWidth;
			mSpriteClips[i].y = 0;
			mSpriteClips[i].w = mWidth;
			mSpriteClips[i].h = mHeight;
		}
	}
}

void MainObject::render() {
	if (playerStatus == WALK_LEFT) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else{
		flip = SDL_FLIP_NONE;
	}
	SDL_Rect* currentClip = &mSpriteClips[frame / 10];
	mPlayerTexture.render(mPosX, mPosY, currentClip, NULL, NULL, flip);
	frame++;
	if (frame / 10 >= ANIMATION_FRAMES) frame = 0;
}

void MainObject::handleInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: mVelY -= POS_VEL; break;
		case SDLK_DOWN: mVelY += POS_VEL; break;
		case SDLK_RIGHT:
			{
			cout << "RIGHT" << endl;
				mVelX += POS_VEL; 
				playerStatus = WALK_RIGHT;
			}
			break;
		case SDLK_LEFT:
			{
			cout << "LEFT" << endl;
				mVelX -= POS_VEL;
				playerStatus = WALK_LEFT;
			}
			break;
		}
		
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: mVelY += POS_VEL; break;
		case SDLK_DOWN: mVelY -= POS_VEL; break;
		case SDLK_RIGHT: mVelX -= POS_VEL; break;
		case SDLK_LEFT: mVelX += POS_VEL; break;
		}
	}
}

void MainObject::move() {
	mPosX += mVelX;
	if (mPosX < 0 || (mPosX + mWidth) > 1280) {
		mPosX -= mVelX;
	}
	mPosY += mVelY;
	if (mPosY < 0 || (mPosY + mHeight) > 640) {
		mPosY -= mVelY;
	}
}