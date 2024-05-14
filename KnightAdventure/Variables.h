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
#include "LevelFinish.h"
#include "LevelControl.h"
#include "LevelSelect.h"
#include "AboutMenu.h"
#include "Potion.h"

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
LevelFinish levelFinish;
LevelControl levelControl;
LevelSelect levelSelect;
AboutMenu aboutMenu;

SDL_Renderer* Game::gRenderer = nullptr;

float scrollingOffset = 0;

vector<Enemy*> Enemy_list;
vector<Potion*> Potion_list;
vector<bool> collisionStatus(20);
vector<bool> potionCollistionStatus(10);
vector<int> beingAttackedStatus(20);

int playerHealth = 0;

int x1, x2, y, trapCollisionTime = 0;
int checkPoint = 0;

bool pauseGame = false;
bool playGame = false;
bool currentLevelFinish = false;
bool homeScreen = true;
bool finishSoundEnd = true;
int currentLevel = 0;

Mix_Music* themeMusic = NULL;
Mix_Music* playMusic = NULL;
Mix_Chunk* buttonSound = NULL;
Mix_Chunk* hitSound = NULL;
Mix_Chunk* finishSound = NULL;
Mix_Chunk* attackSound = NULL;
Mix_Chunk* buffSound = NULL;
Mix_Chunk* enemyHit = NULL;
