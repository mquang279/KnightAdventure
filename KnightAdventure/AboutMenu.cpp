#include "AboutMenu.h"

AboutMenu::AboutMenu() {
	mWidth = 0;
	mHeight = 0;
	frame = 0;
	posChange = 0;
	backState = false;
}

AboutMenu::~AboutMenu() {

}

void AboutMenu::loadMenu() {
	background.loadFromFile("assets/game_state/AboutMenu/about.png");
	button.loadFromFile("assets/game_state/button/newbutton.png");
	textButton.loadFromRenderedText("BACK", { 7, 15, 43 }, 80);
	mWidth = button.getWidth() / 2;
	mHeight = button.getHeight();
	buttonPos = { (1280 - mWidth) / 2, 540 };
	for (int i = 0; i < 2; i++) {
		spriteClips[i].x = i * mWidth;
		spriteClips[i].y = 0;
		spriteClips[i].w = mWidth;
		spriteClips[i].h = mHeight;
	}
}

void AboutMenu::render(SDL_Event& e) {
	background.render(0, 0);
	button.render(buttonPos.x, buttonPos.y, &spriteClips[frame]);
	textButton.render((1280 - textButton.getWidth()) / 2, 536 + posChange);
}

void AboutMenu::handleEvent(SDL_Event& e) {
	if (checkMouseEvent(e, buttonPos)) {
		frame = 1;
		posChange = 12;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			backState = true;
		}
	}
	else {
		frame = 0;
		posChange = 0;
	}
}

bool AboutMenu::checkMouseEvent(SDL_Event& e, SDL_Rect a) {
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

bool AboutMenu::getBackState() {
	return backState;
}
void AboutMenu::setBackState(bool state){
	backState = state;
}