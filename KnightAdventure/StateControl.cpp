#include "StateControl.h"

StateControl* StateControl::get() {
	return &mStateControl;
}

void StateControl::setNextState(GameState* newState) {
	if (mNextState != ExitState::get()) {
		mNextState = newState;
	}
}

void StateControl::changeState() {
	if (mNextState != NULL) {
		mCurrentState->exit();
		mNextState->enter();

		mCurrentState = mNextState;
		mNextState = NULL;
	}
}
