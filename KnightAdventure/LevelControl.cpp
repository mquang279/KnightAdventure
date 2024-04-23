#include "LevelControl.h"

LevelControl::LevelControl() {
}

LevelControl::~LevelControl() {

}

void LevelControl::loadLevel(int level) {
	loadPicture.loadFromFile("assets/game_state/LoadLevel/levelshow.png");
	SDL_Color textColor = { 7, 15, 43 };
	headerTexture.loadFromFile("assets/level/header.png");
	currentLevel.loadFromRenderedText("Level " + to_string(level), textColor, 160);
	ground = new Map();
	grass = new Map();
	trap = new Map();
	ground->loadTileSet("assets/level/tileset2.png");
	trap->loadTileSet("assets/level/traptileset.png");
	grass->loadTileSet("assets/level/tileset2.png");
	ground->createTilesSprites();
	grass->createTilesSprites();
	trap->createTilesSprites();
	trap->loadMap("assets/level/level" + to_string(level) + "/" + "level" + to_string(level) + "_final_trap.map");
	ground->loadMap("assets/level/level" + to_string(level) + "/" + "level" + to_string(level) + "_final_ground.map");
	grass->loadMap("assets/level/level" + to_string(level) + "/" + "level" + to_string(level) + "_final_grass.map");
}

void LevelControl::renderLoadScreen(int level) {
	if (frame < 90) {
		currentLevel.render((1280 - currentLevel.getWidth()) / 2, (640 - currentLevel.getHeight())/ 2);
		frame++;
	}
}

void LevelControl::renderLevel(int level, int mapX) {
	trap->drawMap(mapX);
	ground->drawMap(mapX);
	grass->drawMap(mapX);
	//headerTexture.render(1280 - headerTexture.getWidth() + 20, 0);
	//currentLevel.render(1280 - currentLevel.getWidth() - 30, 16);
}

Map* LevelControl::getCurrentGround(int level) {
	return ground;
}
Map* LevelControl::getCurrentGrass(int level){
	return grass;
}
Map* LevelControl::getCurrentTrap(int level){
	return trap;
}

void LevelControl::setFrame(int x) {
	frame = x;
}