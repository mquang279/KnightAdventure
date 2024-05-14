#include "GameMenu.h"

GameMenu::GameMenu() {
	mWidth = 0;
	mHeight = 0;
	playState = false;
	aboutState = false;
	helpState = false;
}

void GameMenu::loadMenu() {
	menuTexture.loadFromFile("assets/game_state/HomeMenu/background.png");
	SDL_Color textColor = { 7, 15, 43 };
	text[PLAY_TEXT].loadFromRenderedText("PLAY", textColor, 80);
	text[HELP_TEXT].loadFromRenderedText("HELP", textColor, 80);
	text[ABOUT_TEXT].loadFromRenderedText("ABOUT", textColor, 80);
	mainText.loadFromRenderedText("KNIGHT ADVENTURE", textColor, 140);
	for (int i = 0; i < menuItemNum; i++) {
		menuItem[i].loadFromFile("assets/game_state/button/newbutton.png");
	}
	mWidth = menuItem[0].getWidth() / 2;
	mHeight = menuItem[0].getHeight();
	for (int i = 0; i < 2; i++) {
		spriteClips[i].x = i * mWidth;
		spriteClips[i].y = 0;
		spriteClips[i].w = mWidth;
		spriteClips[i].h = mHeight;
	}
}

void GameMenu::render(SDL_Event& e, Mix_Chunk buttonSound) {
	
	menuTexture.render(0, 0);
	playState = false;
	helpState = false;
	aboutState = false;
	for (int i = 0; i < menuItemNum; i++) {
		//Hover Effect
		menuItemPos = { (1280 - mWidth) / 2, 260 + i * 120, 0, 0};
		if (checkMouseEvent(e, menuItemPos)) {
			menuItem[i].render(menuItemPos.x, menuItemPos.y, &spriteClips[1]);
			text[i].render((1280 - text[i].getWidth()) / 2, 255 + i * 120 + 12);
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				Mix_PlayChannel(-1, &buttonSound, 0);
				switch (i) {
					case 0:
						playState = true;
						break;
					case 1:
						helpState = true;
						break;
					case 2:
						aboutState = true;
						break;
				}
			}
		}
		else {
			menuItem[i].render(menuItemPos.x, menuItemPos.y, &spriteClips[0]);
			text[i].render((1280 - text[i].getWidth()) / 2, 255 + i * 120);
		}
	}
	mainText.render((1280 - mainText.getWidth()) / 2, 70);
}

bool GameMenu::checkMouseEvent(SDL_Event& e, SDL_Rect a) {
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

bool GameMenu::getPlayState() {
	return playState;
}

bool GameMenu::getHelpState() {
	return helpState;
}

bool GameMenu::getAboutState() {
	return aboutState;
}

void GameMenu::setPlayState(bool state) {
	playState = state;
}

void GameMenu::setHelpState(bool state){
	helpState = state;
}

void GameMenu::setAboutState(bool state){
	aboutState = state;
}