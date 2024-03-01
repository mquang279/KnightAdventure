#pragma once
#include "Game.h"
#include "LTexture.h"

class Map {
public:
	Map();
	~Map();
	void loadMap();
	void drawMap();
	void createTilesSprites();
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
	const int TOTAL_TILES = 4800;
	const int TOTAL_TILES_ROW = 240;
	const int TOTAL_TILES_COL = 20;
	const int TOTAL_TILES_SPRITES = 1160;
private:
	SDL_Rect src, dest;
	SDL_Rect gTileClip[1160];
	LTexture mTileTexture;
	int map[20][240];

};