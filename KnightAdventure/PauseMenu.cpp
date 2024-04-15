#include "PauseMenu.h"

PauseMenu::PauseMenu() {
	mWidth = 0;
	mHeight = 0;
	for (int i = 0; i < buttonNum; i++) {
		state[i] = false;
	}
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::loadMenu() {
	for (int i = 0; i < buttonNum; i++) {
		button[i].loadFromFile("assets/game_state/button/newbutton.png");
	}
	mWidth = button[0].getWidth() / 2;
	mHeight = button[0].getHeight();
	for (int i = 0; i < buttonNum; i++) {
		buttonPos[i] = { (1280 - mWidth) / 2, 310 + i * 120, mWidth, mHeight };
	}
	SDL_Color textColor = { 50, 50, 58 };
	text[CONTINUE_BUTTON].loadFromRenderedText("CONTINUE", textColor, 80);	
	text[HOME_BUTTON].loadFromRenderedText("HOME", textColor, 80);
	mainText.loadFromRenderedText("KNIGHT ADVENTURE", textColor, 140);
	for (int i = 0; i < 2; i++) {
		spriteClips[i].x = i * mWidth;
		spriteClips[i].y = 0;
		spriteClips[i].w = mWidth;
		spriteClips[i].h = mHeight;
	}
}

void PauseMenu::render(SDL_Event& e) {
	for (int i = 0; i < buttonNum; i++) {
		state[i] = false;
	}
	for (int i = 0; i < buttonNum; i++) {
		if (checkMouseEvent(e, buttonPos[i])) {
			button[i].render(buttonPos[i].x, buttonPos[i].y, &spriteClips[1]);
			posChange[i] = 12;
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				state[i] = true;
			}
		}
		else {
			button[i].render(buttonPos[i].x, buttonPos[i].y, &spriteClips[0]);
			posChange[i] = 0;
		}
	}

	mainText.render((1280 - mainText.getWidth()) / 2, 90);
	for (int i = 0; i < buttonNum; i++) {
		text[i].render((1280 - text[i].getWidth()) / 2 , 304 + i * 120 + posChange[i]);
	}
}

bool PauseMenu::checkMouseEvent(SDL_Event& e, SDL_Rect a) {
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

bool PauseMenu::getContinueState() {
	return state[CONTINUE_BUTTON];
}
bool PauseMenu::getHomeState(){
	return state[HOME_BUTTON];
}



