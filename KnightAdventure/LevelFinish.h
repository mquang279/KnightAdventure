#pragma once

#include "Game.h"
#include "LTexture.h"

class LevelFinish {
public:
	enum buttonType {
		NEXT_LEVEL_BUTTON = 0,
		HOME_BUTTON = 1,
	};
	static const int buttonNum = 2;
	LevelFinish();
	~LevelFinish();
	void loadMenu();
	void render(SDL_Event& e);
	bool checkMouseEvent(SDL_Event& e, SDL_Rect a);
	bool getHomeState();
	bool getNextLevelState();
	void setHomeState(bool status);
	void setNextLevelState(bool status);
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