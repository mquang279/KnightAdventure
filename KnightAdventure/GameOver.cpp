#include "GameOver.h"

GameOver::GameOver() {
	homeState = false;
	replayState = false;
	mWidth = 0;
	mHeight = 0;
	posChange = 0;
}

GameOver::~GameOver() {

}

void GameOver::loadText() {
	SDL_Color textColor = { 255, 255, 255 };
	mReplayText.loadFromRenderedText("PLAY AGAIN", textColor, 80);
	mHomeText.loadFromRenderedText("HOME", textColor, 80);
	mGameOverText.loadFromRenderedText("GAME OVER", { 255, 0, 0 }, 200);
	mReplayButton.loadFromFile("assets/game_state/button/button.png");
	mHomeButton.loadFromFile("assets/game_state/button/button.png");
	mWidth = mReplayButton.getWidth() / 2;
	mHeight = mReplayButton.getHeight();
	for (int i = 0; i < 2; i++) {
		spriteClips[i].x = i * mWidth;
		spriteClips[i].y = 0;
		spriteClips[i].w = mWidth;
		spriteClips[i].h = mHeight;
	}
}

void GameOver::render(SDL_Event& e) {
	homeState = false;
	replayState = false;
	mButtonPos = { (1280 - mWidth) / 2, 300, 0, 0};
	if (checkMouse(e, mButtonPos)) {
		mHomeButton.render(mButtonPos.x, mButtonPos.y, &spriteClips[1]);
		posChange = 5;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			homeState = true;
		}
	}
	else {
		mHomeButton.render(mButtonPos.x, mButtonPos.y, &spriteClips[0]);
		posChange = 0;
	}
	mHomeText.render((1280 - mHomeText.getWidth()) / 2, 306 + posChange);

	mButtonPos = { (1280 - mWidth) / 2, 450, 0, 0 };
	if (checkMouse(e, mButtonPos)) {
		mReplayButton.render(mButtonPos.x, mButtonPos.y, &spriteClips[1]);
		posChange = 5;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			replayState = true;
		}
	}
	else {
		mReplayButton.render(mButtonPos.x, mButtonPos.y, &spriteClips[0]);
		posChange = 0;
	}
	mReplayText.render((1280 - mReplayText.getWidth()) / 2, 456 + posChange);
	mGameOverText.render((1280 - mGameOverText.getWidth()) / 2, 110);
}

bool GameOver::checkMouse(SDL_Event& e, SDL_Rect a) {
	bool inside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < a.x) {
		inside = false;
	}
	else if (x > a.x + mWidth) {
		inside = false;
	}
	else if (y < a.y) {
		inside = false;
	}
	else if (y > a.y + mHeight) {
		inside = false;
	}
	return inside;
}