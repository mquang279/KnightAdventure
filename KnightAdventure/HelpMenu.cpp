#include "HelpMenu.h"

HelpMenu::HelpMenu() {
	mBackHeight = 0;
	mBackWidth = 0;
	mWidth = 0;
	mHeight = 0;
	frame = 0;
	exitButton = { 470,540,340,60 };
	exitState = false;
}

HelpMenu::~HelpMenu() {

}

bool HelpMenu::loadMenu(string path1, string path2) {
	bool success = mHelpBackground.loadFromFile(path1.c_str()) && mAnimation.loadFromFile(path2.c_str());
	if (success) {
		SDL_Color textColor = { 255, 255, 255 };
		mHelpText.loadFromRenderedText("BACK", textColor);
		mBackWidth = mHelpBackground.getWidth();
		mBackHeight = mHelpBackground.getHeight();
		mWidth = mAnimation.getWidth() / 8;
		mHeight = mAnimation.getHeight() / 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 8; j++) {
				mSpriteClips[i][j].x = j * 160;
				mSpriteClips[i][j].y = i * 160;
				mSpriteClips[i][j].w = 160;
				mSpriteClips[i][j].h = 160;
			}
		}
	}
	return success;
}

void HelpMenu::render(SDL_Event& e) {
	exitState = false;
	mHelpBackground.render(0, 0);
	mAnimation.render(135, 220, &mSpriteClips[1][frame / 9]);
	mAnimation.render(560, 220, &mSpriteClips[0][frame / 9]);
	mAnimation.render(985, 220, &mSpriteClips[2][frame / 9]);
	SDL_SetRenderDrawBlendMode(Game::gRenderer, SDL_BLENDMODE_BLEND);
	if (checkMouse(e, exitButton)) {
		SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 225);
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			exitState = true;
		}
	}
	else SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 150);
	SDL_RenderFillRect(Game::gRenderer, &exitButton);
	mHelpText.render((1280 - mHelpText.getWidth()) / 2, 540 - 4);
	frame++;
	if (frame / 9 >= 8) frame = 0;
}

bool HelpMenu::checkMouse(SDL_Event& e, SDL_Rect a) {
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

bool HelpMenu::getExitState() {
	return exitState;
}