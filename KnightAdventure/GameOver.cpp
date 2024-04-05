#include "GameOver.h"

GameOver::GameOver() {
	mReplayButton = { 470, 300, 340, 60 };
	mHomeButton = { 470, 420, 340, 60 };
	homeState = false;
	replayState = false;
}

GameOver::~GameOver() {

}

bool GameOver::loadText() {
	SDL_Color textColor = { 255, 255, 255 };
	bool success = mReplayText.loadFromRenderedText("REPLAY", textColor) && mHomeText.loadFromRenderedText("HOME", textColor) && mGameOverText.loadFromRenderedText("GAME OVER", textColor);
	return success;
}

void GameOver::render(SDL_Event& e) {
	homeState = false;
	replayState = false;
	SDL_SetRenderDrawBlendMode(Game::gRenderer, SDL_BLENDMODE_BLEND);
	if (checkMouse(e, mHomeButton)) {
		SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 225);
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			homeState = true;
		}
	}
	else SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 150);
	SDL_RenderFillRect(Game::gRenderer, &mHomeButton);
	if (checkMouse(e, mReplayButton)) {
		SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 225);
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			replayState = true;
		}
	}
	else SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 150);
	SDL_RenderFillRect(Game::gRenderer, &mReplayButton);
	mReplayText.render((1280 - mReplayText.getWidth()) / 2, 300 - 5);
	mHomeText.render((1280 - mHomeText.getWidth()) / 2, 420 - 5);
	mGameOverText.render(470, 150);
}

bool GameOver::checkMouse(SDL_Event& e, SDL_Rect a) {
	bool inside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < a.x) {
		inside = false;
	}
	else if (x > a.x + a.w) {
		inside = false;
	}
	else if (y < a.y) {
		inside = false;
	}
	else if (y > a.y + a.h) {
		inside = false;
	}
	return inside;
}