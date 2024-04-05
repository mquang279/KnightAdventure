#pragma once
#include "Game.h"
#include "LTexture.h"

class HelpMenu {
public:
	HelpMenu();
	~HelpMenu();
	bool loadMenu(string path1, string path2);
	void render(SDL_Event& e);
	bool checkMouse(SDL_Event& e, SDL_Rect a);
	bool getExitState();
private:
	bool exitState;
	int mBackWidth, mBackHeight;
	int frame;
	int mWidth, mHeight;
	SDL_Rect exitButton;
	SDL_Rect mSpriteClips[3][8];
	LTexture mHelpBackground;
	LTexture mAnimation;
	LTexture mHelpText;
};