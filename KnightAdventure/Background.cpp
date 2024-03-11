#include "Background.h"

BGTexture::BGTexture() {
	mPosBGX = 0;
	mPosBGY = 0;
	mBGWidth = 0;
	mBGHeight = 0;
}

bool BGTexture::loadBackground(string path) {
	bool success = mBackground.loadFromFile(path.c_str());
	if (success) {
		mBGWidth = mBackground.getWidth();
		mBGHeight = mBackground.getHeight();
	}
	return success;
}

void BGTexture::render(int x, int y) {
	mBackground.render(x, y);
}

int BGTexture::getBGHeight() {
	return mBGHeight;
}

int BGTexture::getBGWidth() {
	return mBGWidth;
}
