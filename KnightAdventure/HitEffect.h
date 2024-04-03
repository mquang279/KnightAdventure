#pragma once

#include "Game.h"
#include "LTexture.h"

class HitEffect {
public:
	HitEffect();
	~HitEffect();
	bool loadFromFile(string path);
	void render();
private:
	LTexture mHitEffect;
};