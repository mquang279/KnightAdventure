#include "Game.h"
#include "LTexture.h"
#include "Map.h"
#include "MainObject.h"
#include "Background.h"
#include "Enemy.h"
#include "HealthBar.h"

BGTexture BGFarGround;
BGTexture BGSea;
BGTexture BGSky;
MainObject playerObj;
BGTexture BGClouds;
HealthBar Health_Bar;

Map* map;
Map* grass;

SDL_Renderer* Game::gRenderer = nullptr;

float scrollingOffset = 0;

vector<Enemy*> Enemy_list;
vector<bool> collisionStatus(20);
vector<int> beingAttackedStatus(20);

int playerHealth = 0;


vector<Enemy*> createEnemyList() {
	vector<Enemy*> list_enemy;
	Enemy* enemy_obj = new Enemy[20];
	for (int i = 0; i < 20; i++) {
		Enemy* p_enemy = enemy_obj + i;
		if (p_enemy != NULL) {
			int randomNum = rand() % 2 + 1;
			p_enemy->setEnemyFrames(randomNum);
			if (randomNum == 1) {
				p_enemy->loadImage("assets/enemy/dog/dog-run.png");
				p_enemy->loadDeathImage("assets/enemy/dog/dog-death.png");
			}
			else if (randomNum == 2) {
				p_enemy->loadImage("assets/enemy/burning-ghoul/burning-ghoul.png");
				p_enemy->loadDeathImage("assets/enemy/burning-ghoul/ghoul-death.png");
			}
			p_enemy->setSpriteClips();
			p_enemy->setPosX(1280 + rand() % 300 + i * 800);
			p_enemy->setPosY(0);
			list_enemy.push_back(p_enemy);
		}
	}
	return list_enemy;
}

Game::Game() {
	gWindow = NULL;
	isRunning = true;
}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	srand(time(nullptr));
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
	playerObj.loadDeadImage("assets/characters/dead.png");
	BGClouds.loadBackground("assets/background/clouds2.png");
	BGFarGround.loadBackground("assets/background/far-grounds2.png");
	BGSea.loadBackground("assets/background/sea2.png");
	BGSky.loadBackground("assets/background/sky4.png");
	Enemy_list = createEnemyList();
	playerObj.setSpriteClips();
	map = new Map();
	grass = new Map();
	map->loadMap("assets/level/level1_final_ground.map");
	grass->loadMap("assets/level/level1_final_grass.map");
	map->createTilesSprites();
	grass->createTilesSprites();
	Health_Bar.loadImage();
	BGClouds.loadBackground("assets/background/clouds2.png");
	for (int i = 0; i < 20; i++) {
		collisionStatus[i] = false;
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
	Health_Bar.render();
	BGClouds.render(scrollingOffset, SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
	BGClouds.render(scrollingOffset + BGClouds.getBGWidth(), SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
	BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getBGHeight());
	map->drawMap(playerObj.getMapX());
	grass->drawMap(playerObj.getMapX());
	for (int i = 0; i < Enemy_list.size(); i++) {
		Enemy* p_enemy = Enemy_list[i];
		if (p_enemy != NULL) {
			p_enemy->move(*map);
		}

		//Player Attack Collision
		if (playerObj.getAttackTime() >= 10 && playerObj.getPlayerStatus() == 3 && checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerAttackHitbox()) && !collisionStatus[i] && playerObj.getPlayerCurrentFrame() / 6 >= 3) {
			collisionStatus[i] = true;
		}
		if (!collisionStatus[i]) {
			p_enemy->render(playerObj.getMapX());
		}
		else if (collisionStatus[i] == true){
			p_enemy->renderDieFrame(playerObj.getMapX());
		}

		//Enemy Attack Collision
		if (checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerHitbox()) && !collisionStatus[i] && beingAttackedStatus[i] % 50 == 0 && playerHealth != 8) {
			playerHealth++;
			Health_Bar.setSpriteFrame(playerHealth);
		}
		if (checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerHitbox()) && !collisionStatus[i]) {
			beingAttackedStatus[i]++;
		}
	}
	
	if (playerHealth < 8) {
		playerObj.move(*map);
		playerObj.render();
	}
	else {
		playerObj.renderDeadFrame();
	}
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

bool Game::checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}