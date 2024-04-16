#pragma once

#include "Game.h"
#include "LTexture.h"

class GameOver {
public:
	GameOver();
	~GameOver();
	void loadText();
	void render(SDL_Event& e);
	bool checkMouse(SDL_Event& e, SDL_Rect a);
	bool getReplayState() { return replayState; };
	bool getHomeState() { return homeState; };
private:
	LTexture mReplayButton;
	LTexture mHomeButton;
	SDL_Rect mButtonPos;
	LTexture mReplayText;
	LTexture mHomeText;
	LTexture mGameOverText;
	SDL_Rect spriteClips[2];
	bool homeState;
	bool replayState;
	int mWidth, mHeight;
	int posChange;
};