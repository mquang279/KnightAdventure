#pragma once

#include "Game.h"
#include "LTexture.h"

const int TOTAL_TILES_ROW = 720;
const int TOTAL_TILES_COL = 20;
const int BLANK_TILE = 1;

class Map {
public:
	Map();
	~Map();
	void loadMap(string path);
	void loadTileSet(string path);
	void drawMap(int mapX);
	void createTilesSprites();
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
	const int TOTAL_TILES = 14400;
	const int TOTAL_TILES_SPRITES = 1160;
	int map[20][720];
private:
	SDL_Rect src, dest;
	SDL_Rect gTileClip[1160];
	LTexture mTileTexture;
	int mWidth, mHeight;
};