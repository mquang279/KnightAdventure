#include "LTexture.h"
#include "Map.h"
#include "MainObject.h"
#include "Background.h"
#include "Enemy.h"
#include "HealthBar.h"
#include "HitEffect.h"
#include "GameMenu.h"
#include "HelpMenu.h"
#include "GameOver.h"
#include "PauseMenu.h"

BGTexture BGFarGround;
BGTexture BGSea;
BGTexture BGSky;
MainObject playerObj;
BGTexture BGClouds;
HealthBar Health_Bar;
HitEffect PlayerHitEffect;

GameMenu gameMenu;
HelpMenu helpMenu;
GameOver gameOver;
PauseMenu pauseMenu;

Map* map;
Map* grass;
Map* trap;

SDL_Renderer* Game::gRenderer = nullptr;

float scrollingOffset = 0;

vector<Enemy*> Enemy_list;
vector<bool> collisionStatus(20);
vector<int> beingAttackedStatus(20);

int playerHealth = 0;

int x1, x2, y, trapCollisionTime = 0;

bool pauseGame = false;
int pauseCheck = 1;
bool playGame = false;