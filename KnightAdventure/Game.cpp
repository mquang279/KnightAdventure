#include "Game.h"
#include "Variables.h"

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
			p_enemy->setPosX(1280 + rand() % 300 + i * 1000);
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
		SDL_SetWindowIcon(gWindow, IMG_Load("assets/logo/logo.png"));
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}
		isRunning = true;
	}
}

void Game::loadMedia() {
	//Load Player Object
	playerObj.loadImage("assets/characters/playerAnimation.png");
	playerObj.reload();
	//Load Game State
	gameMenu.loadMenu("assets/game_state/HomeMenu/background.png");
	helpMenu.loadMenu("assets/game_state/HelpMenu/help2.png", "assets/game_state/HelpMenu/animation.png");
	gameOver.loadText();
	pauseMenu.loadMenu();
	// Load Background Start

	BGClouds.loadBackground("assets/background/clouds2.png");
	BGFarGround.loadBackground("assets/background/far-grounds2.png");
	BGSea.loadBackground("assets/background/sea2.png");
	BGSky.loadBackground("assets/background/sky4.png");

	//Load Background End

	PlayerHitEffect.loadFromFile("assets/hit_effect/blood.png");
	Enemy_list = createEnemyList();
	playerObj.setSpriteClips();

	// Load Map Start

	map = new Map();
	grass = new Map();
	trap = new Map();
	trap->loadTileSet("assets/level/traptileset.png");
	map->loadTileSet("assets/level/tileset2.png");
	grass->loadTileSet("assets/level/tileset2.png");
	map->loadMap("assets/level/level1_final_ground.map");
	grass->loadMap("assets/level/level1_final_grass.map");
	trap->loadMap("assets/level/level1_final_trap.map");
	map->createTilesSprites();
	grass->createTilesSprites();
	trap->createTilesSprites();

	// Load Map End

	BGClouds.loadBackground("assets/background/clouds2.png");
	for (int i = 0; i < 20; i++) {
		collisionStatus[i] = false;
	}

	playerHealth = 0;
	Health_Bar.loadImage();
	Health_Bar.setSpriteFrame(playerHealth);

}


void Game::handleEvent(){
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
	if (gameMenu.getPlayState() && !pauseGame) {
		playGame = true;
		scrollingOffset -= 0.5;
		if (scrollingOffset < -BGClouds.getBGWidth()) scrollingOffset = 0;
		BGSky.render(0, 0);
		BGClouds.render(scrollingOffset, SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGClouds.render(scrollingOffset + BGClouds.getBGWidth(), SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getBGHeight());
		map->drawMap(playerObj.getMapX());
		grass->drawMap(playerObj.getMapX());
		trap->drawMap(playerObj.getMapX());

		// Attack Collision Start

		for (int i = 0; i < Enemy_list.size(); i++) {
			Enemy* p_enemy = Enemy_list[i];
			if (p_enemy != NULL) {
				p_enemy->move(*map, *trap);
			}

			//Player Attack Collision
			if (playerObj.getAttackTime() >= 10 && playerObj.getPlayerStatus() == 3 && checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerAttackHitbox()) && !collisionStatus[i] && playerObj.getPlayerCurrentFrame() / 6 >= 3) {
				collisionStatus[i] = true;
			}
			if (!collisionStatus[i]) {
				p_enemy->render(playerObj.getMapX(), pauseGame);
			}
			else if (collisionStatus[i] == true) {
				p_enemy->renderDieFrame(playerObj.getMapX());
			}

			//Enemy Attack Collision

			if (checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerHitbox()) && !collisionStatus[i] && beingAttackedStatus[i] % 80 == 0 && playerHealth != 8 && !playerObj.getDeadStatus()) {
				playerHealth++;
				Health_Bar.setSpriteFrame(playerHealth);
				PlayerHitEffect.render();
			}
			if (checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerHitbox()) && !collisionStatus[i] && playerHealth < 8 && !playerObj.getDeadStatus()) {
				beingAttackedStatus[i]++;
				PlayerHitEffect.render();
			}
		}

		// Attack Collision End

		// Trap Collision Start
		x1 = playerObj.getPlayerHitbox().x + playerObj.getMapX();
		x2 = playerObj.getPlayerHitbox().x + playerObj.getMapX() + playerObj.getPlayerHitbox().w;
		y = playerObj.getPlayerHitbox().y + playerObj.getPlayerHitbox().h;
		if ((trap->map[y / 32][x1 / 32] != 1 || trap->map[y / 32][x2 / 32] != 1)) {
			if (trapCollisionTime % 100 == 0) {
				playerHealth++;
				Health_Bar.setSpriteFrame(playerHealth);
			}
			PlayerHitEffect.render();
			trapCollisionTime++;
		}
		else trapCollisionTime = 0;

		// Health Status Start

		if (playerObj.getPosY() >= 1000) {
			Health_Bar.setSpriteFrame(playerHealth);
			playerObj.setPosX(0);
			playerObj.setPosY(0);
		}

		if (playerObj.getPosY() == 800) {
			playerHealth++;
		}

		if (playerObj.getPosY() >= 640) {
			PlayerHitEffect.render();
		}
		if (playerHealth < 8) {
			playerObj.move(*map);
			playerObj.render();
		}
		else {
			PlayerHitEffect.render();
			playerObj.renderDeadFrame();
			if (playerObj.getDeadStatus()) {
				gameOver.render(e);
				if (gameOver.getHomeState()) {
					gameMenu.setPlayState(false);
					loadMedia();
				}
				else if (gameOver.getReplayState()) {
					loadMedia();
				}
			}
		}
		Health_Bar.render();
		// Health Status End
	}
	else if (gameMenu.getHelpState() && !pauseGame) {
		helpMenu.render(e);
		if (helpMenu.getExitState()) {
			gameMenu.setHelpState(false);
		}
		playGame = false;
	}
	else if (!pauseGame) {
		gameMenu.render(e);
		playGame = false;
	}
	else if (pauseGame){
		BGSky.render(0, 0);
		BGClouds.render(scrollingOffset, SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGClouds.render(scrollingOffset + BGClouds.getBGWidth(), SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getBGHeight());
		map->drawMap(playerObj.getMapX());
		grass->drawMap(playerObj.getMapX());
		trap->drawMap(playerObj.getMapX());
		for (int i = 0; i < Enemy_list.size(); i++) {
			Enemy* p_enemy = Enemy_list[i];
			if (!collisionStatus[i]) {
				p_enemy->render(playerObj.getMapX(), pauseGame);
			}
		}
		playerObj.renderIdleFrame();
		Health_Bar.render();
		pauseMenu.render(e);
	}
	if (pauseGame) {
		if (pauseMenu.getContinueState()) {
			pauseGame = false;
			pauseCheck *= -1;
		}
		if (pauseMenu.getHomeState()) {
			gameMenu.setPlayState(false);
			loadMedia();
			pauseGame = false;
			pauseCheck *= -1;
		}
	}
	if (e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0 && e.type == SDL_KEYDOWN && playGame && playerObj.getOnGroundStatus()) {
		pauseCheck *= -1;
		cout << "ESC" << " " << pauseCheck << endl;
		if (pauseCheck == -1) pauseGame = true;
		else pauseGame = false;
	}
	SDL_RenderPresent(gRenderer);
}

void Game::close(){
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
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

bool trapCollision(SDL_Rect a, int mp[20][720], int trapTile) {
	int x1, x2, y;
	x1 = a.x;
	x2 = a.x + a.w;
	y = a.y + a.h;
	if (mp[x1][y] == trapTile || mp[x2][y] == trapTile) {
		return true;
	}
	return false;
}
