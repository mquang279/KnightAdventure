#include "Game.h"
#include "LTexture.h"
#include "Map.h"
#include "MainObject.h"

LTexture BGClouds;
LTexture BGFarGround;
LTexture BGSea;
LTexture BGSky;
MainObject playerObj;

Map* map;
Map* grass;

SDL_Renderer* Game::gRenderer = nullptr;


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
	BGClouds.loadFromFile("assets/background/clouds2.png");
	BGFarGround.loadFromFile("assets/background/far-grounds2.png");
	BGSea.loadFromFile("assets/background/sea2.png");
	BGSky.loadFromFile("assets/background/sky3.png");
	playerObj.setSpriteClips();
	map = new Map();
	grass = new Map();
	map->loadMap("assets/level/mapfinal.map");
	grass->loadMap("assets/level/grassfinal.map");
	map->createTilesSprites();
	grass->createTilesSprites();
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

}

void Game::render(){
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	BGSky.render(0, -50);
	BGClouds.render(0, SCREEN_HEIGHT - BGClouds.getHeight() + 100);
	//BGSea.render(0, 384);
	BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getHeight());
	playerObj.move(*map);
	map->drawMap();
	grass->drawMap();
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