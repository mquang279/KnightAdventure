#pragma once
#include "Game.h"
#include "LTexture.h"

const int menuItemNum = 3;

class GameMenu {
public:
	GameMenu();
	~GameMenu() {};
	bool loadMenu(string path);
	void render(SDL_Event& e);
	bool checkMouseEvent(SDL_Event& e, SDL_Rect a);
	bool getPlayState();
	bool getHelpState();
	bool getAboutState();
	void setPlayState(bool state);
	void setHelpState(bool state);
	void setAboutState(bool state);
private:
	LTexture menuTexture;
	LTexture playText;
	LTexture helpText;
	LTexture aboutText;
	bool playState;
	bool helpState;
	bool aboutState;
	int mWidth, mHeight;
	SDL_Rect menuItem[menuItemNum];
};