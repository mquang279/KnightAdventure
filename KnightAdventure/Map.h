#pragma once
#include "Game.h"
#include "LTexture.h"

const int TOTAL_TILES_ROW = 240;
const int TOTAL_TILES_COL = 20;
const int BLANK_TILE = 1;


class Map {
public:
	Map();
	~Map();
	void loadMap(string path);
	void drawMap();
	void createTilesSprites();
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
	const int TOTAL_TILES = 4800;
	const int TOTAL_TILES_SPRITES = 1160;
	int map[20][240];
private:
	SDL_Rect src, dest;
	SDL_Rect gTileClip[1160];
	LTexture mTileTexture;
};