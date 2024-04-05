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
		playText.loadFromRenderedText("PLAY", textColor);
		helpText.loadFromRenderedText("HELP", textColor);
		aboutText.loadFromRenderedText("ABOUT", textColor);
		mWidth = menuTexture.getWidth();
		mHeight = menuTexture.getHeight();
		
		for (int i = 0; i < menuItemNum; i++) {
			menuItem[i].x = 460;
			menuItem[i].y = 260 + i * 100;
			menuItem[i].w = 360;
			menuItem[i].h = 64;
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
		if (checkMouseEvent(e, menuItem[i])) {
			SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 225);
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
		else SDL_SetRenderDrawColor(Game::gRenderer, 0, 104, 56, 150);
		SDL_RenderFillRect(Game::gRenderer, &menuItem[i]);
	}
	playText.render((1280 - playText.getWidth()) / 2, 260 - 4);
	helpText.render((1280 - helpText.getWidth()) / 2, 360 - 4);
	aboutText.render((1280 - aboutText.getWidth()) / 2, 460 - 4);
}

bool GameMenu::checkMouseEvent(SDL_Event& e, SDL_Rect a) {
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