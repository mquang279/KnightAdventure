#include "LevelSelect.h"

LevelSelect::LevelSelect() {
	backState = false;
	textPosChange = 0;
	mBackWidth = 0;
	mBackHeight = 0;
	mButtonHeight = 0;
	mButtonWidth = 0;
}

LevelSelect::~LevelSelect() {

}

void LevelSelect::loadMenu() {
	Background.loadFromFile("assets/game_state/LevelSelect/selectLevel.png");
	SDL_Color textColor = { 7, 15, 43 };
	mainText.loadFromRenderedText("SELECT LEVEL", textColor, 80);
	for (int i = 0; i < TOTAL_LEVEL; i++) {
		levelButton[i].loadFromFile("assets/game_state/LevelSelect/button.png");
		levelNum[i].loadFromRenderedText(to_string(i + 1), textColor, 80);
	}
	BackButton.loadFromFile("assets/game_state/button/newbutton.png");
	mBackWidth = BackButton.getWidth() / 2;
	mBackHeight = BackButton.getHeight();
	mButtonWidth = levelButton[0].getWidth() / 2;
	mButtonHeight = levelButton[0].getHeight();
	backButtonPos = { (1280 - mBackWidth) / 2, 548, mBackWidth, mBackHeight };
	backText.loadFromRenderedText("BACK", textColor, 80);
	for (int i = 0; i < 2; i++) {
		spriteClips[i].x = i * mButtonWidth;
		spriteClips[i].y = 0;
		spriteClips[i].w = mButtonWidth;
		spriteClips[i].h = mButtonHeight;
	}
	for (int i = 0; i < 2; i++) {
		backSpriteClips[i].x = i * mBackWidth;
		backSpriteClips[i].y = 0;
		backSpriteClips[i].w = mBackWidth;
		backSpriteClips[i].h = mBackHeight;
	}
	for (int i = 0; i < TOTAL_LEVEL / 6; i++) {
		for (int j = 0; j < TOTAL_LEVEL / 3; j++) {
			levelButtonPos[i * 6 + j] = {160 + j * 173, 120 + i * 144, mButtonWidth, mButtonHeight};
			levelNumPos[i * 6 + j] = { 160 + j * 173 + (mButtonWidth - levelNum[i * 6 + j].getWidth()) / 2, 120 + i * 144 + (mButtonHeight - levelNum[i * 6 + j].getHeight()) / 2 - 10, 0, 0};
		}
	}
}

void LevelSelect::render(SDL_Event& e) {
	Background.render(0, 0);
	if (checkMouse(e, backButtonPos)) {
		BackButton.render(backButtonPos.x, backButtonPos.y, &backSpriteClips[1]);
		textPosChange = 12;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			backState = true;
		}
	}
	else {
		BackButton.render(backButtonPos.x, backButtonPos.y, &backSpriteClips[0]);
		textPosChange = 0;
	}
	backText.render((1280 - backText.getWidth()) / 2, 542 + textPosChange);
	for (int i = 0; i < TOTAL_LEVEL; i++) {
		if (checkMouse(e, levelButtonPos[i])) {
			levelButton[i].render(levelButtonPos[i].x, levelButtonPos[i].y, &spriteClips[1]);
			textPosChange = 11;
		}
		else {
			levelButton[i].render(levelButtonPos[i].x, levelButtonPos[i].y, &spriteClips[0]);
			textPosChange = 0;
		}
		levelNum[i].render(levelNumPos[i].x, levelNumPos[i].y + textPosChange);
	}
	mainText.render((1280 - mainText.getWidth()) / 2, 40);
}

bool LevelSelect::checkMouse(SDL_Event& e, SDL_Rect a) {
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

bool LevelSelect::getBackState() {
	return backState;
}

int LevelSelect::getSelectLevel(SDL_Event& e) {
	for (int i = 0; i < TOTAL_LEVEL; i++) {
		if (checkMouse(e, levelButtonPos[i])) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				return (i + 1);
			}
		}
	}
	return 0;
}

void LevelSelect::setBackState(bool state) {
	backState = state;
}
