#include "MainObject.h"
#include "Map.h"

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
	inputType.left_ = 0;
	inputType.right_ = 0;
	inputType.up_ = 0;
	inputType.down_ = 0;
	onGround = false;
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
			mSpriteClipsRun[i].x = i * 64;
			mSpriteClipsRun[i].y = 0;
			mSpriteClipsRun[i].w = mWidth;
			mSpriteClipsRun[i].h = mHeight;
		}
	}
}

void MainObject::render() {
	int currentFrame = 0;
	if (playerStatus == WALK_LEFT) {
		flip = SDL_FLIP_HORIZONTAL;
		currentFrame = ANIMATION_FRAMES;
		mPlayerTexture.loadFromFile("assets/characters/running.png");
	}
	else if (playerStatus == WALK_RIGHT){
		flip = SDL_FLIP_NONE;
		currentFrame = ANIMATION_FRAMES;
		mPlayerTexture.loadFromFile("assets/characters/running.png");

	}
	if (mVelX == 0 && mVelY == 0) {
		mPlayerTexture.loadFromFile("assets/characters/idle.png");
		currentFrame = IDLE_FRAMES;
	}
	SDL_Rect* currentClip = &mSpriteClipsRun[frame / 10];
	mPlayerTexture.render(mPosX - mapX, mPosY + 10, currentClip, NULL, NULL, flip);
	//SDL_Rect hitBox = { mPosX - mapX, mPosY + 10, mWidth, mHeight };
	SDL_SetRenderDrawColor(Game::gRenderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(Game::gRenderer, &hitBox);
	frame++;
	if (frame / 10 >= currentFrame) frame = 0;
}

void MainObject::handleInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
		{
			inputType.right_ = 1;
			inputType.left_ = 0;
			playerStatus = WALK_RIGHT;
		}
		break;
		case SDLK_LEFT:
		{
			inputType.right_ = 0;
			inputType.left_ = 1;
			playerStatus = WALK_LEFT;
		}
		break;
		case SDLK_UP:
		{
			inputType.up_ = 1;
		}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT: inputType.right_ = 0; break;
		case SDLK_LEFT: inputType.left_ = 0; break;
		case SDLK_UP: inputType.up_ = 0; break;
		}
	}

}

void MainObject::move(Map& map_data) {
	mVelX = 0;
	mVelY += GRAVITY_SPEED;
	if (mVelY > MAX_GRAVITY_SPEED) {
		mVelY = MAX_GRAVITY_SPEED;
	}
	if (inputType.left_ == 1) {
		mVelX -= POS_VEL;
	}
	else if (inputType.right_ == 1) {
		mVelX += POS_VEL;
	}

	if (inputType.up_ == 1) {
		if (onGround){
			mVelY = -JUMP_VAL;
		}
		inputType.up_ = 0;
	}

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int height_min = 0;

	// Xu li va cham theo chieu doc
	if (mHeight < TILE_SIZE) {
		height_min = mHeight;
	}
	else height_min = TILE_SIZE;
	x1 = (mPosX + mVelX) / TILE_SIZE;
	x2 = (mPosX + mVelX + mWidth - 1) / TILE_SIZE;

	y1 = (mPosY) / TILE_SIZE;
	y2 = (mPosY + height_min - 1) / TILE_SIZE;
	onGround = false;

	if (x1 >= 0 && x2 < TOTAL_TILES_ROW && y1 >= 0 && y2 < TOTAL_TILES_COL) {
		//Nhan vat di chuyen sang phai
		if (mVelX > 0) {
			if (map_data.map[y1][x2] != BLANK_TILE || map_data.map[y2][x2] != BLANK_TILE){
				mPosX = x2 * TILE_SIZE;
				mPosX -= mWidth + 1;
				mVelX = 0;
			}
		}
		//Nhan vat di chuyen sang trai
		else if (mVelX < 0) {
			if (map_data.map[y1][x1] != BLANK_TILE || map_data.map[y2][x1] != BLANK_TILE){
				mPosX = (x1 + 1) * TILE_SIZE;
				mVelX = 0;
			}
		}
	}

	//Xu li va cham theo chieu ngang

	int width_min = 0;
	if (mWidth < TILE_SIZE) width_min = mWidth;
	else width_min = TILE_SIZE;
	x1 = (mPosX) / TILE_SIZE;
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
		mPosX = 0;
	}
	if ((mPosX + mWidth) > TOTAL_TILES_ROW * TILE_SIZE) {
		mPosX = TOTAL_TILES_ROW * TILE_SIZE - mWidth - 1;
	}
	centerEntityOnMap();
}

void MainObject::centerEntityOnMap() {
	if (mPosY < 640) {
		mapX = mPosX - (1280 / 2);
	}
	if (mapX < 0) {
		mapX = 0;
	}
	else if (mapX + 1280 >= TOTAL_TILES_ROW * TILE_SIZE) {
		mapX = TOTAL_TILES_ROW * TILE_SIZE - 1280;
	}
}

int MainObject::getMapX() {
	return mapX;
}

