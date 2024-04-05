#pragma once
#include "Game.h"
#include "LTexture.h"

class GameOver {
public:
	GameOver();
	~GameOver();
	bool loadText();
	void render(SDL_Event& e);
	bool checkMouse(SDL_Event& e, SDL_Rect a);
	bool getReplayState() { return replayState; };
	bool getHomeState() { return homeState; };
private:
	SDL_Rect mReplayButton;
	SDL_Rect mHomeButton;
	LTexture mReplayText;
	LTexture mHomeText;
	LTexture mGameOverText;
	bool homeState;
	bool replayState;
};