#include "Game.h"
#include "Variables.h"

vector<Enemy*> createEnemyList() {
	vector<Enemy*> list_enemy;
	Enemy* enemy_obj = new Enemy[20];
	for (int i = 0; i < 20; i++) {
		Enemy* p_enemy = enemy_obj + i;
		if (p_enemy != NULL) {
			int randomNum = rand() % 3 + 1;
			p_enemy->setEnemyFrames(randomNum);
			if (randomNum == 1) {
				p_enemy->loadImage("assets/enemy/dog/dog-run.png");
				p_enemy->loadDeathImage("assets/enemy/dog/dog-death.png");
			}
			else if (randomNum == 2) {
				p_enemy->loadImage("assets/enemy/burning-ghoul/burning-ghoul.png");
				p_enemy->loadDeathImage("assets/enemy/burning-ghoul/ghoul-death.png");
			}
			else if (randomNum == 3) {
				p_enemy->loadImage("assets/enemy/ghost/ghost.png");
				p_enemy->loadDeathImage("assets/enemy/ghost/ghost-death.png");
			}
			p_enemy->setSpriteClips();
			p_enemy->setPosX(1280 + rand() % 300 + i * 1000);
			p_enemy->setPosY(0);
			list_enemy.push_back(p_enemy);
		}
	}
	return list_enemy;
}

vector<Potion*> createPotionList() {
	vector<Potion*> list_Potion;
	Potion* potion_obj = new Potion[10];
	for (int i = 0; i < 10; i++) {
		Potion* p_potion = potion_obj + i;
		if (p_potion != NULL) {
			p_potion->loadPotion(6000 + rand() % 600 + i * 4500);
			list_Potion.push_back(p_potion);
		}
	}
	return list_Potion;
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
		if (!(Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3))
		{
			cout << "Sound can not initilize!" << Mix_GetError() << endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		isRunning = true;
	}
}

void Game::loadMedia() {
	//Load Player Object
	playerObj.loadImage("assets/characters/playerAnimation.png");
	playerObj.reload();
	playerObj.setSpriteClips();
	//Load Game State
	gameMenu.loadMenu();
	helpMenu.loadMenu();
	gameOver.loadText();
	pauseMenu.loadMenu();
	levelFinish.loadMenu();
	levelSelect.loadMenu();
	aboutMenu.loadMenu();
	// Load Background Start
	BGClouds.loadBackground("assets/background/clouds2.png");
	BGFarGround.loadBackground("assets/background/far-grounds2.png");
	BGSea.loadBackground("assets/background/sea2.png");
	BGSky.loadBackground("assets/background/sky4.png");
	//Load Background End

	//Enemy Load Start
	Enemy_list = createEnemyList();
	for (int i = 0; i < 20; i++) {
		collisionStatus[i] = false;
	}
	//Enemy Load End

	themeMusic = Mix_LoadMUS("assets/sfx/game_theme.mp3");
	playMusic = Mix_LoadMUS("assets/sfx/game_theme.mp3");
	buttonSound = Mix_LoadWAV("assets/sfx/button.mp3");
	hitSound = Mix_LoadWAV("assets/sfx/playerhit.wav");
	finishSound = Mix_LoadWAV("assets/sfx/levelfinish.wav");
	buffSound = Mix_LoadWAV("assets/sfx/buff.mp3");
	enemyHit = Mix_LoadWAV("assets/sfx/enemyhit.mp3");

	//Health Add
	Potion_list = createPotionList();
	PlayerHitEffect.loadFromFile("assets/hit_effect/blood.png");
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
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(themeMusic, -1);
	}
	//Home Render Start
	if (homeScreen) {
		gameMenu.render(e, *buttonSound);
		currentLevel = 0;
		
	}
	//Home Render End
	//Select Level Menu Start
	if (gameMenu.getPlayState()) {
		if (!homeScreen) {
			currentLevel = levelSelect.getSelectLevel(e);
			if (currentLevel != 0) {
				playerObj.setBuffFinish(false);
				checkPoint = 0;
				levelControl.loadLevel(currentLevel);
				//levelControl.setFrame(0);
				for (int i = 0; i < Potion_list.size(); i++) {
					Potion_list[i]->setPosY(*levelControl.getCurrentGround(currentLevel), *levelControl.getCurrentTrap(currentLevel) , playerObj.getMapX());
				}
			}
		}
		homeScreen = false;
		levelSelect.render(e);
		if (levelSelect.getBackState()) {
			homeScreen = true;
			levelSelect.setBackState(false);
			gameMenu.setPlayState(false);
		}
	}
	//Select Level Menu End
	// 
	//Help Menu Start
	if (gameMenu.getHelpState()) {
		homeScreen = false;
		helpMenu.render(e);
		if (helpMenu.getExitState()) {
			helpMenu.setExitState(false);
			homeScreen = true;
			gameMenu.setHelpState(false);
		}
	}
	//Help Menu End

	//About Menu Start

	if (gameMenu.getAboutState()) {
		if (!homeScreen) {
			aboutMenu.handleEvent(e);
		}
		homeScreen = false;
		if (aboutMenu.getBackState()) {
			homeScreen = true;	
			aboutMenu.setBackState(false);
			gameMenu.setAboutState(false);
		}
		aboutMenu.render(e);
	}
	//About Menu End

	//In Game Start
	if (currentLevel != 0 && !pauseGame) {
		gameMenu.setPlayState(false);
		playGame = true;
		scrollingOffset -= 0.5;
		if (scrollingOffset < -BGClouds.getBGWidth()) scrollingOffset = 0;
		BGSky.render(0, 0);
		BGClouds.render(scrollingOffset, SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGClouds.render(scrollingOffset + BGClouds.getBGWidth(), SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getBGHeight());
		levelControl.renderLevel(currentLevel, playerObj.getMapX());
		// Attack Collision Start
		for (int i = 0; i < Potion_list.size(); i++) {
			if (!potionCollistionStatus[i]) {
				Potion_list[i]->render(playerObj.getMapX());
			}
			if (checkCollision(Potion_list[i]->getPotionHitbox(), playerObj.getPlayerHitbox()) && !potionCollistionStatus[i]) {
				if (playerHealth != 0) {
					playerHealth--;
					Health_Bar.setSpriteFrame(playerHealth);
					Health_Bar.render();
				}
				Mix_PlayChannel(-1, buffSound, 0);
				potionCollistionStatus[i] = true;
				playerObj.setBuffFinish(false);
			}
			if (potionCollistionStatus[i] && !playerObj.getBuffFinish()) {
				playerObj.renderBuffEffect();
			}
		}
		for (int i = 0; i < Enemy_list.size(); i++) {
			Enemy* p_enemy = Enemy_list[i];
			if (p_enemy != NULL && !p_enemy->getTrapHit()) {
				p_enemy->move(*levelControl.getCurrentGround(currentLevel), *levelControl.getCurrentTrap(currentLevel));
				//Player Attack Collision
				if (abs((playerObj.getPlayerHitbox().y + playerObj.getPlayerHitbox().h) - (p_enemy->getPosY() + p_enemy->getHeight()) <= 10) && playerObj.getAttackTime() >= 10 && playerObj.getPlayerStatus() == 3 && checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerAttackHitbox()) && !collisionStatus[i] && playerObj.getPlayerCurrentFrame() / 6 >= 3) {
					collisionStatus[i] = true;
					Mix_PlayChannel(-1, enemyHit, 0);
				}
				if (!collisionStatus[i]) {
					p_enemy->render(playerObj.getMapX(), pauseGame);
				}
				else if (collisionStatus[i] == true) {
					p_enemy->renderDieFrame(playerObj.getMapX());
				}

				//Enemy Attack Collision

				if (checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerHitbox()) && !collisionStatus[i] && beingAttackedStatus[i] % 80 == 0 && playerHealth != 8 && !playerObj.getDeadStatus() && p_enemy->getPosY() <= 640) {
					playerHealth++;
					Mix_PlayChannel(-1, hitSound, 0);
					Health_Bar.setSpriteFrame(playerHealth);
					PlayerHitEffect.render();
				}
				if (checkCollision(p_enemy->getEnemyHitbox(), playerObj.getPlayerHitbox()) && !collisionStatus[i] && playerHealth < 8 && !playerObj.getDeadStatus()) {
					beingAttackedStatus[i]++;
					PlayerHitEffect.render();
				}
			}
		}

		

		// Attack Collision End

		// Trap Collision Start
		x1 = playerObj.getPlayerHitbox().x + playerObj.getMapX();
		x2 = playerObj.getPlayerHitbox().x + playerObj.getMapX() + playerObj.getPlayerHitbox().w;
		y = playerObj.getPlayerHitbox().y + playerObj.getPlayerHitbox().h;
		if ((levelControl.getCurrentTrap(currentLevel)->map[y / 32][x1 / 32] != 1 || levelControl.getCurrentTrap(currentLevel)->map[y / 32][x2 / 32] != 1)) {
			if (trapCollisionTime % 100 == 0 && playerHealth < 8) {
				Mix_PlayChannel(-1, hitSound, 0);
				playerHealth++;
				Health_Bar.setSpriteFrame(playerHealth);
			}
			PlayerHitEffect.render();
			trapCollisionTime++;
		}
		else trapCollisionTime = 0;

		// Health Status Start
		if (playerObj.getPosX() >= TOTAL_TILES_ROW * 32 * 2 / 3 && checkPoint < TOTAL_TILES_ROW * 32 * 2 / 3 && playerObj.getPosY() < 640) {
			checkPoint = TOTAL_TILES_ROW * 32 * 2 / 3;
			Mix_PlayChannel(-1, buffSound, 0);
			playerObj.setBuffFinish(false);
		}
		else if (playerObj.getPosX() >= TOTAL_TILES_ROW * 32 / 3 && checkPoint < TOTAL_TILES_ROW * 32 / 3 && playerObj.getPosY() < 640) {
			checkPoint = TOTAL_TILES_ROW * 32 / 3;
			Mix_PlayChannel(-1, buffSound, 0);
			playerObj.setBuffFinish(false);
		}
		if (playerObj.getPosY() >= 1400) {
			playerObj.setBuffFinish(false);
			Health_Bar.setSpriteFrame(playerHealth);
			playerObj.setPosX(checkPoint);
			playerObj.setPosY(0);
		}

		if (playerObj.getPosY() == 1200) {
			Mix_PlayChannel(-1, hitSound, 0);
			playerHealth++;
		}

		//

		if (playerObj.getPosY() >= 640) {
			PlayerHitEffect.render();
		}
		if ((playerHealth < 8 && !currentLevelFinish)) {
			playerObj.move(*levelControl.getCurrentGround(currentLevel));
			playerObj.render();
			playerObj.renderBuffEffect();
		}
		else if (!playerObj.getOnGroundStatus()) {
			playerObj.move(*levelControl.getCurrentGround(currentLevel));
			playerObj.render();
		}
		else if (!currentLevelFinish && playerObj.getOnGroundStatus()) {
			PlayerHitEffect.render();
			playerObj.renderDeadFrame();
			if (playerObj.getDeadStatus()) {
				gameOver.render(e);
				if (gameOver.getHomeState()) {
					gameMenu.setPlayState(false);
					homeScreen = true;
					reload();
				}
				else if (gameOver.getReplayState()) {
					reload();
				}
			}
		}
		else {
			playerObj.renderIdleFrame();
		}
		Health_Bar.render();
		if (playerObj.getPosX() >= (TOTAL_TILES_ROW * 32 - 170)) {
			currentLevelFinish = true;
		}
		if (currentLevelFinish) {
			levelFinish.render(e);
		}
		if (!playerObj.getBuffFinish()) {
			playerObj.renderBuffEffect();
		}
		// Health Status End
		levelControl.renderLoadScreen(currentLevel);
	}
	//In Game End

	//Pause Game Start
	if (pauseGame) {
		BGSky.render(0, 0);
		BGClouds.render(scrollingOffset, SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGClouds.render(scrollingOffset + BGClouds.getBGWidth(), SCREEN_HEIGHT - BGClouds.getBGHeight() + 100);
		BGFarGround.render(0, SCREEN_HEIGHT - BGFarGround.getBGHeight());
		levelControl.renderLevel(currentLevel, playerObj.getMapX());
		for (int i = 0; i < Enemy_list.size(); i++) {
			Enemy* p_enemy = Enemy_list[i];
			if (!collisionStatus[i]) {
				p_enemy->render(playerObj.getMapX(), pauseGame);
			}
		}
		playerObj.renderIdleFrame();
		Health_Bar.render();
		pauseMenu.render(e);
		if (pauseMenu.getContinueState()) {
			pauseGame = false;
		}
		if (pauseMenu.getHomeState()) {
			gameMenu.setPlayState(false);
			homeScreen = true;
			//loadMedia();
			reload();
			pauseGame = false;
		}
	}
	if (!homeScreen && e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0 && e.type == SDL_KEYDOWN && playGame && playerObj.getOnGroundStatus()) {
		pauseGame = !pauseGame;
	}
	//Pause Game End

	//Level Finish Start
	if (levelFinish.getHomeState()) {
		homeScreen = true;
		reload();
		gameMenu.setPlayState(false);
		levelFinish.setHomeState(false);
		currentLevelFinish = false;
	}
	if (levelFinish.getNextLevelState() && currentLevel < 18) {
		Mix_PlayChannel(-1, finishSound, 0);
		currentLevel++;
		currentLevelFinish = false;
		levelControl.loadLevel(currentLevel);
		levelFinish.setNextLevelState(false);
		//levelControl.setFrame(0);
		reload();
	}
	else if (levelFinish.getNextLevelState()) homeScreen = true;
	//cout << currentLevel << endl;
	//Level Finish End
	SDL_RenderPresent(gRenderer);
}

void Game::reload() {
	checkPoint = 0;
	//Player Reload
	playerObj.reload();
	//Health Reload
	playerHealth = 0;
	Health_Bar.setSpriteFrame(playerHealth);
	Health_Bar.loadImage();
	//Enemy Reload
	Enemy_list = createEnemyList();
	for (int i = 0; i < 20; i++) {
		collisionStatus[i] = false;
	}
	Potion_list = createPotionList();
	for (int i = 0; i < Potion_list.size(); i++) {
		potionCollistionStatus[i] = false;
		Potion_list[i]->setPosY(*levelControl.getCurrentGround(currentLevel), *levelControl.getCurrentTrap(currentLevel), playerObj.getMapX());
	}
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
	y = a.y + a.h - 3;
	if (mp[x1 / 32][y / 32] == trapTile || mp[x2 / 32][y / 32] == trapTile) {
		return true;
	}
	return false;
}


