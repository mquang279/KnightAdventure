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
	const int TOTAL_TILES = 1600;
	const int TOTAL_TILES_ROW = 40;
	const int TOTAL_TILES_COL = 20;
	const int TOTAL_TILES_SPRITES = 256;
private:
	SDL_Rect src, dest;
	SDL_Rect gTileClip[256];
	LTexture mTileTexture;
	int map[20][80];

};