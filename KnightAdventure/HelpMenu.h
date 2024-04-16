#pragma once

#include "Game.h"
#include "LTexture.h"

class HelpMenu {
public:
	HelpMenu();
	~HelpMenu();
	void loadMenu();
	void render(SDL_Event& e);
	bool checkMouse(SDL_Event& e, SDL_Rect a);
	bool getExitState();
	void setExitState(bool state);
private:
	bool exitState;
	int textPosChange;
	int mButtonWidth, mButtonHeight;
	int frame;
	int mWidth, mHeight;
	SDL_Rect mSpriteClips[3][8];
	SDL_Rect exitButtonPos;
	LTexture moveText;
	LTexture attackText;
	LTexture jumpText;
	LTexture mHelpBackground;
	LTexture mAnimation;
	LTexture mHelpText;
	LTexture exitButton;
	SDL_Rect spriteClips[2];
};