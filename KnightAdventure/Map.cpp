#include "Map.h"
#include "LTexture.h"


Map::Map() {
	src.x = src.y = 0;
	src.w = dest.w = 0;
	src.h = dest.h = 0;
	dest.x = dest.y = 0;
	mWidth = 0;
	mHeight = 0;

}

void Map::createTilesSprites() {
	int xPos = 0, yPos = 0;
	for (int i = 0; i < TOTAL_TILES_SPRITES; i++) {
		gTileClip[i].x = xPos;
		gTileClip[i].y = yPos;
		gTileClip[i].w = TILE_WIDTH;
		gTileClip[i].h = TILE_HEIGHT;
		//cout << gTileClip[i].x << " " << gTileClip[i].y << " " << gTileClip[i].w << " " << gTileClip[i].h << endl;
		xPos += 32;
		if (xPos >= mWidth) {
			xPos = 0;
			yPos += 32;
		}
	}
}

void Map::loadTileSet(string path) {
	mTileTexture.loadFromFile(path.c_str());
	mWidth = mTileTexture.getWidth();
	mHeight = mTileTexture.getHeight();
}

void Map::loadMap(string path) {
	ifstream mp(path.c_str());
	int x = 0, y = 0;
	if (mp.fail()) cout << "failed" << endl;
	for (int i = 0; i < TOTAL_TILES; i++) {
		int tileType = -1;
		mp >> tileType;
		if ((tileType >= 0) && (tileType < TOTAL_TILES_SPRITES)) {
			map[y][x] = tileType;
		}
		//cout << tileType << " ";
		x++;
		if (x >= TOTAL_TILES_ROW) {
			//cout << endl;
			x = 0;
			y++;
		}
	}
}

void Map::drawMap(int mapX) {
	int type = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 720; j++) {
			type = map[i][j];
			//cout << type << endl;
			dest.x = j * 32;
			dest.y = i * 32;
			//cout << dest.x << " " << dest.y << " " << map[i][j] << endl;
			mTileTexture.render(dest.x - mapX, dest.y, &gTileClip[type]);
		}
	}
}
