#pragma once

#include "Game.h"
#include "LTexture.h"

class AboutMenu {
public:
	AboutMenu();
	~AboutMenu();
	void loadMenu();
	void render(SDL_Event& e);
	bool checkMouseEvent(SDL_Event& e, SDL_Rect a);
	bool getBackState();
	void setBackState(bool state);
	void handleEvent(SDL_Event& e);
private:
	int mWidth, mHeight, frame, posChange;
	LTexture background;
	LTexture button;
	LTexture textButton;
	SDL_Rect buttonPos;
	SDL_Rect spriteClips[2];
	bool backState;
};