#include "IntroState.h"
#include "StateControl.h"
#include "LevelState.h"

LevelState* LevelState::get() {
	return &sLevelState;
}

bool LevelState::enter() {
	bool success = true;

	if (!mBackgroundTexture.loadFromFile("assets/game_state/intro_state/intro_state.png")) {
		success = false;
	}

	return success;
}

bool LevelState::exit() {
	mBackgroundTexture.free();
	return true;
}

void LevelState::handleEvent(SDL_Event& e) {
	if (e.key.keysym.sym == SDLK_r) {
		StateControl::setNextState()Level