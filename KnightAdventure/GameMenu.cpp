#include "GameMenu.h"

GameMenu::GameMenu() {
	mWidth = 0;
	mHeight = 0;
	playState = false;
	aboutState = false;
	helpState = false;
}

bool GameMenu::loadMenu(string path) {
	bool success = true;
	if (!menuTexture.loadFromFile(path.c_str())) {
		success = false;
	}
	else {
		SDL_Color textColor = { 255, 255, 255 };
		playText.loadFromRenderedText("PLAY", textColor, 80);
		helpText.loadFromRenderedText("HELP", textColor, 80);
		aboutText.loadFromRenderedText("ABOUT", textColor, 80);
		for (int i = 0; i < menuItemNum; i++) {
			menuItem[i].loadFromFile("assets/game_state/button/buttonall.png");
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
	return success;
}

void GameMenu::render(SDL_Event& e) {
	
	menuTexture.render(0, 0);
	SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 200);
	SDL_SetRenderDrawBlendMode(Game::gRenderer, SDL_BLENDMODE_BLEND);
	playState = false;
	helpState = false;
	aboutState = false;
	for (int i = 0; i < menuItemNum; i++) {
		//Hover Effect
		menuItemPos = { 470, 280 + i * 100, 0, 0 };
		if (checkMouseEvent(e, menuItemPos)) {
			menuItem[i].render(menuItemPos.x, menuItemPos.y, &spriteClips[1]);
			posChange[i] = 5;
			if (e.type == SDL_MOUSEBUTTONDOWN) {
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
			posChange[i] = 0;
		}
	}
	playText.render((1280 - playText.getWidth()) / 2, 286 + posChange[0]);
	helpText.render((1280 - helpText.getWidth()) / 2, 386 + posChange[1]);
	aboutText.render((1280 - aboutText.getWidth()) / 2, 486 + posChange[2]);
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