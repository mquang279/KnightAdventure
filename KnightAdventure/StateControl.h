#pragma once
#include "GameState.h"

class StateControl {
public:
	static StateControl* get();
	void setNextState(GameState* newState);
	void changeState();

private:
	StateControl();
	static StateControl mStateControl;
	GameState* mCurrentState;
	GameState* mNextState;
};