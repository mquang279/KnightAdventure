#pragma once

#include "Game.h"
#include "LTexture.h"

class BGTexture {
public:
	BGTexture();
	void render(int x, int y);
	bool loadBackground(string path);
	int getBGWidth();
	int getBGHeight();
private:
	LTexture mBackground;
	int mPosBGX, mPosBGY;
	int mBGWidth, mBGHeight;
};