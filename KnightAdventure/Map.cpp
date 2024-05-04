#include "Map.h"
#include "LTexture.h"


Map::Map() {
	src.x = src.y = 0;
	src.w = dest.w = 0;
	src.h = dest.h = 0;
	dest.x = dest.y = 0;
	mWidth = 0;
	mHeight = 0;
	portalWidth = 0;
	portalHeight = 0;
	frame = 0;
	yPortal = 0;
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
	for (int i = 0; i < 6; i++) {
		portalClips[i].x = i * portalWidth;
		portalClips[i].y = 0;
		portalClips[i].w = portalWidth;
		portalClips[i].h = portalHeight;

	}
}

void Map::loadTileSet(string path) {
	mTileTexture.loadFromFile(path.c_str());
	portalTexture.loadFromFile("assets/portal/portal.png");
	mWidth = mTileTexture.getWidth();
	mHeight = mTileTexture.getHeight();
	portalWidth = portalTexture.getWidth() / 6;
	portalHeight = portalTexture.getHeight();
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

void Map::setPortalPosY() {
	for (int i = 0; i < TOTAL_TILES_COL; i++) {
		if (map[i][715] != 1) {
			yPortal = i * 32;
			break;
		}
	}
}

void Map::renderPortal(int mapX) {
	portalTexture.render(TOTAL_TILES_ROW * 32 - 240 - mapX, yPortal - portalHeight, &portalClips[frame / 8]);
	frame++;
	if (frame / 8 >= 6) {
		frame = 0;
	}
}