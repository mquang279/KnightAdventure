#include "HitEffect.h"

HitEffect::HitEffect() {

}

HitEffect::~HitEffect() {

}

bool HitEffect::loadFromFile(string path) {
	bool success = mHitEffect.loadFromFile(path.c_str());
	return success;
}

void HitEffect::render() {
	mHitEffect.render(0, 0);
}