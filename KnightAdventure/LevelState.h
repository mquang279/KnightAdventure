#pragma once
#include "Game.h"
#include "GameState.h"
#include "LTexture.h"

class LevelState : public GameState {
public:
	static LevelState* get();

	bool enter();
	bool exit();

	void handleEvent(SDL_Event& e);
	void update();
	void render();
private:
	static LevelState sLevelState;
	LevelState();
	LTexture mBackgroundTexture;

};