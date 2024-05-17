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
	void renderLoadScreen(int level);
	Map* getCurrentGround(int level);
	Map* getCurrentGrass(int level);
	Map* getCurrentTrap(int level);
	//void setFrame(int x);
private:
	Map* ground;
	Map* grass;
	Map* trap;
	LTexture headerTexture;
	LTexture currentLevel;
	LTexture loadPicture;
	int frameStart;
};