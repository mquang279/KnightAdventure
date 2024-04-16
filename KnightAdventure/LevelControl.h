#pragma once

#include "Game.h"
#include "Map.h"
#include <string>


class LevelControl {
public:
	static const int TOTAL_LEVEL = 18;
	LevelControl();
	~LevelControl();
	void loadLevel(int level);
	void renderLevel(int level, int mapX);
	Map* getCurrentGround(int level);
	Map* getCurrentGrass(int level);
	Map* getCurrentTrap(int level);
private:
	Map* ground;
	Map* grass;
	Map* trap;
	LTexture headerTexture;
	LTexture currentLevel;
};