#include "HelpMenu.h"

HelpMenu::HelpMenu() {
	mButtonHeight = 0;
	mButtonWidth = 0;
	mWidth = 0;
	mHeight = 0;
	frame = 0;
	exitState = false;
	textPosChange = 0;
}

HelpMenu::~HelpMenu() {

}

void HelpMenu::loadMenu() {
	mHelpBackground.loadFromFile("assets/game_state/HelpMenu/help.png");
	mAnimation.loadFromFile("assets/game_state/HelpMenu/animation.png");
	mWidth = mAnimation.getWidth() / 8;
	mHeight = mAnimation.getHeight() / 3;
	exitButton.loadFromFile("assets/game_state/button/newbutton.png");
	mButtonWidth = exitButton.getWidth() / 2;
	mButtonHeight = exitButton.getHeight();
	exitButtonPos = { (1280 - mButtonWidth) / 2,530, 0, 0 };
	SDL_Color textColor = { 7, 15, 43 };
	mHelpText.loadFromRenderedText("BACK", textColor, 80);
	moveText.loadFromRenderedText("MOVE", textColor, 90);
	attackText.loadFromRenderedText("ATTACK", textColor, 90);
	jumpText.loadFromRenderedText("JUMP", textColor, 90);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			mSpriteClips[i][j].x = j * 160;
			mSpriteClips[i][j].y = i * 160;
			mSpriteClips[i][j].w = 160;
			mSpriteClips[i][j].h = 160;
		}
	}
	for (int i = 0; i < 2; i++) {
		spriteClips[i].x = i * mButtonWidth;
		spriteClips[i].y = 0;
		spriteClips[i].w = mButtonWidth;
		spriteClips[i].h = mButtonHeight;
	}
}

void HelpMenu::render(SDL_Event& e) {
	exitState = false;
	mHelpBackground.render(0, 0);
	mAnimation.render(145, 220, &mSpriteClips[1][frame / 9]);
	mAnimation.render(560, 220, &mSpriteClips[0][frame / 9]);
	mAnimation.render(985, 220, &mSpriteClips[2][frame / 9]);
	if (checkMouse(e, exitButtonPos)) {
		exitButton.render(exitButtonPos.x, exitButtonPos.y, &spriteClips[1]);
		textPosChange = 12;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			exitState = true;
		}
	}
	else {
		exitButton.render(exitButtonPos.x, exitButtonPos.y, &spriteClips[0]);
		textPosChange = 0;
	}
	mHelpText.render((1280 - mHelpText.getWidth()) / 2, 526 + textPosChange);
	frame++;
	if (frame / 9 >= 8) frame = 0;
	moveText.render(133, 92);
	attackText.render(514, 92);
	jumpText.render(977, 92);
}

bool HelpMenu::checkMouse(SDL_Event& e, SDL_Rect a) {
	bool inside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < a.x) {
		inside = false;
	}
	else if (x > a.x + mButtonWidth) {
		inside = false;
	}
	else if (y < a.y) {
		inside = false;
	}
	else if (y > a.y + mButtonHeight) {
		inside = false;
	}
	return inside;
}

bool HelpMenu::getExitState() {
	return exitState;
}

void HelpMenu::setExitState(bool state) {
	exitState = state;
}