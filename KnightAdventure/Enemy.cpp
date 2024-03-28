#include "Enemy.h"
#include "MainObject.h"

Enemy::Enemy() {
	onGround = false;
	mPosX = 0;
	mPosY = 0;
	mVelX = -2;
	mVelY = 0;
	frame = 0;
	mWidth = 0;
	mHeight = 0;
	ENEMY_FRAMES = 0;
	dieFinish = false;
	dieFrame = 0;
	flip = SDL_FLIP_NONE;
}

Enemy::~Enemy() {

}

void Enemy::setEnemyFrames(int randomNum) {
	if (randomNum == 1) {
		ENEMY_FRAMES = 5;
	}
	else if (randomNum == 2) {
		ENEMY_FRAMES = 8;
	}
}

bool Enemy::loadImage(string path) {
	bool success = mEnemyTexture.loadFromFile(path.c_str());
	if (success) {
		mWidth = mEnemyTexture.getWidth() / ENEMY_FRAMES;
		mHeight = mEnemyTexture.getHeight();
		mEnemyHitBox.w = mWidth;
		mEnemyHitBox.h = mHeight;
	}
	return success;
}

bool Enemy::loadDeathImage(string path) {
	bool success = mEnemyDie.loadFromFile(path.c_str());
	if (success) {
		mDieWidth = mEnemyDie.getWidth() / ENEMY_DIE_FRAMES;
		mDieHeight = mEnemyDie.getHeight();
	}
	return success;
}

void Enemy::setSpriteClips() {
	for (int i = 0; i < ENEMY_FRAMES; i++) {
		mSpriteClipsEnemy[i].x = i * mWidth;
		mSpriteClipsEnemy[i].y = 0;
		mSpriteClipsEnemy[i].w = mWidth;
		mSpriteClipsEnemy[i].h = mHeight;
	}
	for (int i = 0; i < ENEMY_DIE_FRAMES; i++) {
		mSpriteClipsEnemyDie[i].x = i * mDieWidth;
		mSpriteClipsEnemyDie[i].y = 0;
		mSpriteClipsEnemyDie[i].w = mDieWidth;
		mSpriteClipsEnemyDie[i].h = mDieHeight;
	}
}

void Enemy::render(int mapX) {
	flip = SDL_FLIP_NONE;
	if (mVelX > 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	SDL_SetRenderDrawColor(Game::gRenderer, 255, 0, 0, 255);
	mEnemyHitBox.x = mPosX - mapX;
	mEnemyHitBox.y = mPosY;
	//SDL_RenderDrawRect(Game::gRenderer, &mEnemyHitBox);
	mEnemyTexture.render(mPosX - mapX, mPosY, &mSpriteClipsEnemy[frame / 8], NULL, NULL, flip);
	frame++;
	if (frame / 8 >= ENEMY_FRAMES) {
		frame = 0;
	}
}

void Enemy::renderDieFrame(int mapX) {
	mVelX = 0;
	mVelY = 0;
	if (dieFinish == false) {
		mEnemyDie.render(mPosX - mapX, mPosY, &mSpriteClipsEnemyDie[dieFrame / 6], NULL, NULL, flip);
		dieFrame++;
		if (dieFrame / 6 >= ENEMY_DIE_FRAMES) {
			dieFinish = true;
		}
	}
	
	
}


void Enemy::move(Map& map_data) {
	mVelY += ENEMY_GRAVITY_SPEED;
	if (mVelY > ENEMY_MAX_GRAVITY_SPEED) {
		mVelY = ENEMY_MAX_GRAVITY_SPEED;
	}

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int height_min = 0;

	// Xu li va cham theo chieu ngang
	if (mHeight < TILE_SIZE) {
		height_min = mHeight;
	}
	else height_min = TILE_SIZE;
	x1 = (mPosX + mVelX) / TILE_SIZE;
	x2 = (mPosX + mVelX + mWidth - 1) / TILE_SIZE;

	y1 = (mPosY) / TILE_SIZE + 1;
	y2 = (mPosY + height_min - 1) / TILE_SIZE + 1;
	onGround = false;

	if (x1 >= 0 && x2 < TOTAL_TILES_ROW && y1 >= 0 && y2 < TOTAL_TILES_COL) {
		//Nhan vat di chuyen sang phai
		if (mVelX > 0) {
			if (map_data.map[y1][x2] != BLANK_TILE || map_data.map[y2][x2] != BLANK_TILE) {
				mPosX = x2 * TILE_SIZE;
				mPosX -= mWidth + 1;
				mVelX = -1 * mVelX;
			}
		}
		//Nhan vat di chuyen sang trai
		else if (mVelX < 0) {
			if (map_data.map[y1][x1] != BLANK_TILE || map_data.map[y2][x1] != BLANK_TILE) {
				mPosX = (x1 + 1) * TILE_SIZE;
				mVelX = -1 * mVelX;
			}
		}
	}

	//Xu li va cham theo chieu doc

	int width_min = 0;
	if (mWidth < TILE_SIZE) width_min = mWidth;
	else width_min = TILE_SIZE;
	x1 = (mPosX + width_min - 3) / TILE_SIZE;
	x2 = (mPosX + width_min) / TILE_SIZE;
	y1 = (mPosY + mVelY) / TILE_SIZE;
	y2 = (mPosY + mVelY + mHeight - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < TOTAL_TILES_ROW && y1 >= 0 && y2 < TOTAL_TILES_COL) {
		if (mVelY > 0) {
			if (map_data.map[y2][x1] != BLANK_TILE || map_data.map[y2][x2] != BLANK_TILE) {
				mPosY = y2 * TILE_SIZE;
				mPosY -= (mHeight - 1);
				mVelY = 0;
				onGround = true;
			}
			else mVelX = -1 * mVelX;
		}
		else if (mVelY < 0) {
			if (map_data.map[y1][x1] != BLANK_TILE || map_data.map[y1][x2] != BLANK_TILE) {
				mPosY = (y1 + 1) * TILE_SIZE;
				mVelY = 0;
			}
		}
	}
	mPosX += mVelX;
	mPosY += mVelY;
	if (mPosX < 0) {
		mVelX = -1 * mVelX;
	}
	if ((mPosX + mWidth) > TOTAL_TILES_ROW * TILE_SIZE) {
		mPosX = TOTAL_TILES_ROW * TILE_SIZE - mWidth - 1;
	}
}

int Enemy::getWidth() {
	return mWidth;
}

int Enemy::getHeight() {
	return mHeight;
}

SDL_Rect Enemy::getEnemyHitbox() {
	return mEnemyHitBox;
}

