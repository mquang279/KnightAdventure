#include "IntroState.h"
#include "StateControl.h"
#include "LevelState.h"

IntroState* IntroState::get() {
	return &sIntroState;
}

bool IntroState::enter() {
	bool success = true;

	if (!mBackgroundTexture.loadFromFile("assets/game_state/intro_state/intro_state.png")) {
		success = false;
	}

	return success;
}

bool IntroState::exit() {
	mBackgroundTexture.free();
	return true;
}

void IntroState::handleEvent(SDL_Event& e) {
	if (e.key.keysym.sym == SDLK_r) {
		StateControl::get()->setNextState(LevelState::get());
	}
}