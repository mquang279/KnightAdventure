#pragma once

#include "Game.h"
#include "LTexture.h"

class Portal {
public:
	Portal();
	~Portal();
private:
	LTexture mPortal;
	int mWidth, mHeight;
	int mPosX, mPosY;
};