#pragma once

#include "Game.h"
#include "LTexture.h"
#include "GameMenu.h"

class PauseMenu{
public:
	enum buttonType {
		CONTINUE_BUTTON = 0,
		HOME_BUTTON = 1,
	};
	static const int buttonNum = 2;
	PauseMenu();
	~PauseMenu();
	void loadMenu();
	void render(SDL_Event& e);
	bool checkMouseEvent(SDL_Event& e, SDL_Rect a);
	bool getContinueState();
	bool getHomeState();
	void setPlayState(bool state);
	void setHelpState(bool state);
private:
	LTexture button[buttonNum];
	LTexture text[buttonNum];
	LTexture mainText;
	bool state[buttonNum];
	int mWidth, mHeight;
	SDL_Rect menuItemPos;
	SDL_Rect spriteClips[2];
	SDL_Rect buttonPos[buttonNum];
	int posChange[buttonNum];
};