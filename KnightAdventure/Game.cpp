#include "Game.h"
#include "LTexture.h"
#include "Map.h"

LTexture playerTex;
LTexture BGClouds;
LTexture BGFarGround;
LTexture BGSea;
LTexture BGSky;
Map* map;

int posX = 0, posY = 0;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Rect gSpriteClips[4];

Game::Game() {
	gWindow = NULL;
	isRunning = true;
	frame = 0;
	WALKING_ANIMATION_FRAMES = 4;
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
	playerTex.loadFromFile("assets/characters/idle.png");
	BGClouds.loadFromFile("assets/background/clouds2.png");
	BGFarGround.loadFromFile("assets/background/far-grounds2.png");
	BGSea.loadFromFile("assets/background/sea2.png");
	BGSky.loadFromFile("assets/background/sky3.png");
	map = new Map();
	map->createTilesSprites();
	for (int i = 0; i < 4; i++) {
		gSpriteClips[i].x = i * playerTex.getWidth() / 4;
		gSpriteClips[i].y = 0;
		gSpriteClips[i].w = playerTex.getWidth() / 4;
		gSpriteClips[i].h = playerTex.getHeight();
	}
}


void Game::handleEvent(){
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update(){
	map->loadMap();
}

void Game::render(){
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	SDL_Rect* currentClip = &gSpriteClips[frame / 12];
	BGSky.render(0, -50);
	BGClouds.render(0, SCREEN_HEIGHT - BGClouds.getHeight() + 100);
	//BGSea.render(0, 384);
	BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getHeight());
	playerTex.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);
	map->drawMap();
	SDL_RenderPresent(gRenderer);
	++frame;
	if (frame >= WALKING_ANIMATION_FRAMES * 12)
	{
		frame = 0;
	}
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