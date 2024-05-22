#include "MainObject.h"
#include "Map.h"

MainObject::MainObject() {
	mPlayerHitBoxX = 0;
	mPlayerHitBoxY = 0;
	mPlayerHitBoxH = 0;
	mPlayerHitBoxW = 0;
	mVelX = 0;
	mVelY = 0;
	mPosX = 0;
	mPosY = 0;
	frame = 0;
	mWidth = 0;
	mHeight = 0;
	mFixX = 0;
	mFixY = 0;
	playerStatus = -1;
	flip = SDL_FLIP_NONE;
	inputType.left_ = 0;
	inputType.right_ = 0;
	inputType.up_ = 0;
	inputType.down_ = 0;
	onGround = false;
	attackAnimationFinished = false;
	attackAnimationTime = 0;
	dieFrame = 0;
	isDead = false;
	buffFinish = false;
	buffFrame = 0;
	playerHitBox = { 0,0,0,0 };
}

bool MainObject::loadImage(string path) {
	bool success = mPlayerTexture.loadFromFile(path.c_str());
	mBuffTexture.loadFromFile("assets/characters/buffeffect.png");
	if (success) {
		mWidth = mPlayerTexture.getWidth() / ANIMATION_FRAMES;
		mHeight = mPlayerTexture.getHeight() / TOTAL_ANIMATION;
	}
	for (int i = 0; i < BUFF_FRAME; i++) {
		mSpriteClipsBuff[i].x = i * (mBuffTexture.getWidth() / BUFF_FRAME);
		mSpriteClipsBuff[i].y = 0;
		mSpriteClipsBuff[i].w = mBuffTexture.getWidth() / BUFF_FRAME;
		mSpriteClipsBuff[i].h = mBuffTexture.getHeight();
	}
	return success;
}

void MainObject::setSpriteClips() {
	if (mWidth > 0 && mHeight > 0) {
		for (int i = 0; i < TOTAL_ANIMATION; i++) {
			for (int j = 0; j < ANIMATION_FRAMES; j++) {
				mSpriteClips[i][j].x = j * 144;
				mSpriteClips[i][j].y = i * 128;
				mSpriteClips[i][j].w = mWidth;
				mSpriteClips[i][j].h = mHeight;
			}
		}
	}
}

void MainObject::render() {
	SDL_Rect* currentClip = &mSpriteClips[2][frame / 7];
	attackAnimationFinished = false;
	mFixY = 24;
	mFixX = 0;
	if (playerStatus == WALK_LEFT && inputType.left_ == 1){
		flip = SDL_FLIP_HORIZONTAL;
		currentClip = &mSpriteClips[2][frame / 7];
		mPlayerHitBoxX = 48;
		mPlayerHitBoxY = 32;
		mPlayerHitBoxW = -112;
		mPlayerHitBoxH = -64;
	}
	else if (playerStatus == WALK_RIGHT && inputType.right_ == 1){
		flip = SDL_FLIP_NONE;
		currentClip = &mSpriteClips[2][frame / 7];
		mPlayerHitBoxX = 64;
		mPlayerHitBoxY = 32;
		mPlayerHitBoxW = -112;
		mPlayerHitBoxH = -64;
	}
	if (playerStatus == PLAYER_ATTACK && onGround && mVelX == 0 && mVelY == 0 && inputType.up_ == 0) {
		currentClip = &mSpriteClips[0][frame / 7];
		if (flip == SDL_FLIP_NONE) {
			mFixX = -12;
			mPlayerHitBoxX = 64;
			mPlayerHitBoxY = 32;
			mPlayerHitBoxW = -112;
			mPlayerHitBoxH = -64;

			mAttackHitBoxX = 90;
			mAttackHitBoxY = 0;
			mAttackHitBoxW = -110;
			mAttackHitBoxH = -48;
		}
		else {
			mFixX = 12;
			mPlayerHitBoxX = 48;
			mPlayerHitBoxY = 32;
			mPlayerHitBoxW = -112;
			mPlayerHitBoxH = -64;

			mAttackHitBoxX = 7;
			mAttackHitBoxY = 0;
			mAttackHitBoxW = -65;
			mAttackHitBoxH = -48;
		}
		attackAnimationTime++;
	}
	if (mVelX == 0 && mVelY == 0 && playerStatus != PLAYER_ATTACK && inputType.left_ == 0 && inputType.right_ == 0) {
		currentClip = &mSpriteClips[1][frame / 7];
		if (flip == SDL_FLIP_NONE) {
			mFixX = 14;
			mPlayerHitBoxX = 32;
			mPlayerHitBoxY = 32;
			mPlayerHitBoxW = -112;
			mPlayerHitBoxH = -64;
		}
		else {
			mFixX = -14;
			mPlayerHitBoxX = 80;
			mPlayerHitBoxY = 32;
			mPlayerHitBoxW = -112;
			mPlayerHitBoxH = -64;
		}
	}
	if (mVelY != 0) {
		currentClip = &mSpriteClips[2][0];
		if (flip == SDL_FLIP_NONE) {
			mFixX = -10;
		}
		else {
			mFixX = 10;
		}
	}
	
	mPlayerTexture.render(mPosX - mapX + mFixX, mPosY + mFixY, currentClip, NULL, NULL, flip);
	SDL_Rect hitBox1 = { mPosX - mapX + mFixX + mAttackHitBoxX, mPosY + mFixY + mAttackHitBoxY, mSpriteClips[0][0].w + mAttackHitBoxW, mSpriteClips[0][0].h + mAttackHitBoxH };
	SDL_Rect hitBox2 = { mPosX - mapX + mFixX + mPlayerHitBoxX, mPosY + mFixY + mPlayerHitBoxY, currentClip->w + mPlayerHitBoxW, currentClip->h + mPlayerHitBoxH };
	playerHitBox = hitBox2;
	attackHitBox = hitBox1;
	//SDL_SetRenderDrawColor(Game::gRenderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(Game::gRenderer, &playerHitBox);
	//SDL_RenderDrawRect(Game::gRenderer, &attackHitBox);
	frame++;
	if (frame / 7 >= ANIMATION_FRAMES) frame = 0;
}

void MainObject::renderDeadFrame() {
	if (isDead == false) {
		mPlayerTexture.render(mPosX - mapX, mPosY + 54, &mSpriteClips[3][dieFrame / 10], NULL, NULL, flip);
		dieFrame++;
		if (dieFrame / 10 >= ANIMATION_FRAMES) {
			isDead = true;
		}
	}
	else {
		isDead = true;
		mPlayerTexture.render(mPosX - mapX, mPosY + 54, &mSpriteClips[3][ANIMATION_FRAMES - 1], NULL, NULL, flip);
	}
}

void MainObject::renderIdleFrame() {
	mPlayerTexture.render(mPosX - mapX + mFixX, mPosY + mFixY, &mSpriteClips[1][0], NULL, NULL, flip);
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
			playerStatus = PLAYER_JUMP;
		}
		break;
		case SDLK_SPACE:
		{
			playerStatus = PLAYER_ATTACK;
		}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT: {
			inputType.right_ = 0;
		}
		break;
		case SDLK_LEFT: {
			inputType.left_ = 0;
		}
		break;
		case SDLK_UP: {
			inputType.up_ = 0;
		}
		break;
		case SDLK_SPACE:
		{
			playerStatus = PLAYER_IDLE;
			attackAnimationTime = 0;
		}
		break;
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
		if (onGround && playerStatus != PLAYER_ATTACK){
			mVelY = -JUMP_VAL;
		}
		inputType.up_ = 0;
	}

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int height_min = 0;

	// Xu li va cham theo chieu ngang
	if (mHeight + mPlayerHitBoxH < TILE_SIZE) {
		height_min = mHeight + mPlayerHitBoxH;
	}
	else height_min = TILE_SIZE;
	x1 = (mPosX + mVelX + mPlayerHitBoxX + mFixX) / TILE_SIZE;
	x2 = (mPosX + mVelX + mPlayerHitBoxX + mFixX + mWidth + mPlayerHitBoxW - 1) / TILE_SIZE;
	//y1 va y2 la 2 o chua nhan vat

	y1 = (mPosY + mPlayerHitBoxY) / TILE_SIZE + 1;
	y2 = (mPosY + mPlayerHitBoxY + mWidth + mPlayerHitBoxW - 1) / TILE_SIZE + 1;
	
	onGround = false;

	if (x1 >= 0 && x2 < TOTAL_TILES_ROW && y1 >= 0 && y2 < TOTAL_TILES_COL) {
		//Nhan vat di chuyen sang phai
		if (mVelX > 0) {
			if (map_data.map[y1][x2] != BLANK_TILE || map_data.map[y2][x2] != BLANK_TILE){
				mPosX = x2 * TILE_SIZE;
				mPosX -= (mPlayerHitBoxX + mWidth + mPlayerHitBoxW - 1 + mFixX);
				mVelX = 0;
			}
		}
		//Nhan vat di chuyen sang trai
		else if (mVelX < 0) {
			if (map_data.map[y1][x1] != BLANK_TILE || map_data.map[y2][x1] != BLANK_TILE){
				mPosX = (x1 + 1) * TILE_SIZE - (mPlayerHitBoxX + mFixX);
				mVelX = 0;
			}
		}
	}

	//Xu li va cham theo chieu doc

	int width_min = 0;
	if (mWidth + mPlayerHitBoxW < TILE_SIZE) width_min = mWidth + mPlayerHitBoxW;
	else width_min = TILE_SIZE;

	x1 = (mPosX + mPlayerHitBoxX + mFixX) / TILE_SIZE;
	x2 = (mPosX + mPlayerHitBoxX + mFixX + width_min - 3) / TILE_SIZE;
	y1 = (mPosY + mVelY + mPlayerHitBoxY) / TILE_SIZE + 1;
	y2 = (mPosY + mVelY + mPlayerHitBoxY + mHeight + mPlayerHitBoxH - 1) / TILE_SIZE + 1;
	
	if (x1 >= 0 && x2 < TOTAL_TILES_ROW && y1 >= 0 && y2 < TOTAL_TILES_COL) {
		if (mVelY > 0) {
			if (map_data.map[y2][x1] != BLANK_TILE || map_data.map[y2][x2] != BLANK_TILE) {
				mPosY = (y2 - 1) * TILE_SIZE;
				mPosY -= (mPlayerHitBoxY + mHeight + mPlayerHitBoxH - 1);
				mVelY = 0;
				onGround = true;
			}
		} 
		else if (mVelY < 0) {
			if (map_data.map[y1][x1] != BLANK_TILE || map_data.map[y1][x2] != BLANK_TILE) {
				mPosY = (y1) * TILE_SIZE;
				mVelY = 0;
			}
		}
	}

	if (playerStatus == PLAYER_ATTACK && onGround) {
		mVelX = 0;
		mVelY = 0;
	}
	mPosX += mVelX;
	mPosY += mVelY;
	if (mPosX + mPlayerHitBoxX + mFixX < 0) {
		mPosX = -(mPlayerHitBoxX + mFixX);
	}
	if ((mPosX + mWidth + mPlayerHitBoxW + mPlayerHitBoxX + mFixX) > TOTAL_TILES_ROW * TILE_SIZE) {
		mPosX = TOTAL_TILES_ROW * TILE_SIZE - (mWidth + mPlayerHitBoxW + mPlayerHitBoxX + mFixX + 1);
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

int MainObject::getPosX() {
	return (int)mPosX;
}

int MainObject::getPosY() {
	return (int)mPosY;
}

SDL_Rect MainObject::getPlayerHitbox() {
	return playerHitBox;
}

SDL_Rect MainObject::getPlayerAttackHitbox() {
	return attackHitBox;
}

int MainObject::getPlayerStatus() {
	return playerStatus;
}

int MainObject::getPlayerCurrentFrame() {
	return frame;
}

int MainObject::getAttackTime() {
	return attackAnimationTime;
}

void MainObject::setPosX(int x) {
	mPosX = x;
}

void MainObject::setPosY(int y) {
	mPosY = y;
}

bool MainObject::getDeadStatus() {
	return isDead;
}

void MainObject::reload() {
	dieFrame = 0;
	isDead = false;
	buffFinish = false;
	mPosX = 0;
	mPosY = 0;
}

bool MainObject::getOnGroundStatus() {
	return onGround;
}

void MainObject::renderBuffEffect() {
	if (!buffFinish) {
		mBuffTexture.render( mPosX - mapX + 25, mPosY + 30, &mSpriteClipsBuff[buffFrame / 12], NULL, NULL, flip);
		buffFrame++;
		if (buffFrame / 12 >= BUFF_FRAME) {
			buffFinish = true;
			buffFrame = 0;
		}
	}
}

bool MainObject::getBuffFinish() {
	return buffFinish;
}

void MainObject::setBuffFinish(bool status) {
	buffFinish = status;
}