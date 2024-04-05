#pragma once
#include "Game.h"

class GameState {
public:
	virtual bool enter() = 0;
	virtual bool exit() = 0;

	virtual void handleEvent(SDL_Event& e) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual ~GameState() {};

	void setNextState(GameState* newState);
	void changeState();
};