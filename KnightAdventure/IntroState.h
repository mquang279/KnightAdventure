#pragma once
#include "Game.h"
#include "GameState.h"
#include "LTexture.h"

class IntroState : public GameState {
public:
	static IntroState* get();

	bool enter();
	bool exit();

	void handleEvent(SDL_Event& e);
	void update();
	void render();
private:
	static IntroState sIntroState;
	IntroState();
	LTexture mBackgroundTexture;
	
};