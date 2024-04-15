#include "Game.h"
#include "LTexture.h"
#include "string"

class LevelSelect {
public:
	static const int TOTAL_LEVEL = 18;
	LevelSelect();
	~LevelSelect();
	void loadMenu();
	void render(SDL_Event& e);
	bool checkMouse(SDL_Event& e, SDL_Rect a);
	bool getBackState();
	int getSelectLevel(SDL_Event& e);
	void setBackState(bool state);
private:
	bool backState;
	int textPosChange;
	int mBackWidth, mBackHeight;
	int mButtonWidth, mButtonHeight;
	SDL_Rect backButtonPos;
	SDL_Rect levelButtonPos[TOTAL_LEVEL];
	SDL_Rect levelNumPos[TOTAL_LEVEL];
	LTexture mainText;
	LTexture Background;
	LTexture levelButton[TOTAL_LEVEL];
	LTexture levelNum[TOTAL_LEVEL];
	LTexture BackButton;
	LTexture backText;
	SDL_Rect spriteClips[2];
	SDL_Rect backSpriteClips[2];
	bool levelSelectState[TOTAL_LEVEL];
	int selectedLevel;
};