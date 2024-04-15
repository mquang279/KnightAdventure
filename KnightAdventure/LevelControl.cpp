#include "LevelControl.h"

LevelControl::LevelControl() {
}

LevelControl::~LevelControl() {

}

void LevelControl::loadLevel(int level) {
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

void LevelControl::renderLevel(int level, int mapX) {
	trap->drawMap(mapX);
	ground->drawMap(mapX);
	grass->drawMap(mapX);
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