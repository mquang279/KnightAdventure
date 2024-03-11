#include "Game.h"
#include "LTexture.h"
#include "Map.h"
#include "MainObject.h"
#include "Background.h"

BGTexture BGFarGround;
BGTexture BGSea;
BGTexture BGSky;
MainObject playerObj;
BGTexture BGClouds;

Map* map;
Map* grass;

SDL_Renderer* Game::gRenderer = nullptr;

float scrollingOffset = 0;

Game::Game() {
	gWindow = NULL;
	isRunning = true;
}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		isRunning = false;
	}
	else {
		gWindow = SDL_CreateWindow("Knight Adventure", xpos, ypos, width, height, fullscreen);
		if (gWindow) {
			cout << "Window created!" << endl;
		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer) {
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}
		isRunning = true;
	}
	playerObj.loadImage("assets/characters/running.png");
	BGClouds.loadBackground("assets/background/clouds2.png");
	BGFarGround.loadBackground("assets/background/far-grounds2.png");
	BGSea.loadBackground("assets/background/sea2.png");
	BGSky.loadBackground("assets/background/sky4.png");
	playerObj.setSpriteClips();
	map = new Map();
	grass = new Map();
	map->loadMap("assets/level/mapfinal.map");
	grass->loadMap("assets/level/grassfinal.map");
	map->createTilesSprites();
	grass->createTilesSprites();
	BGClouds.loadBackground("assets/background/clouds2.png");
}


void Game::handleEvent(){
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			playerObj.handleInput(e);
			break;
	}
}

void Game::update(){
	scrollingOffset -= 0.5;
	if (scrollingOffset < -BGClouds.getBGWidth()) scrollingOffset = 0;
}

void Game::render(){
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	BGSky.render(0, 0);
	BGClouds.render(scrollingOffset, SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
	BGClouds.render(scrollingOffset + BGClouds.getBGWidth(), SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
	BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getBGHeight());
	playerObj.move(*map);
	map->drawMap(playerObj.getMapX());
	grass->drawMap(playerObj.getMapX());
	playerObj.render();
	SDL_RenderPresent(gRenderer);
}

void Game::close(){
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

bool Game::running() {
	return isRunning;
}