#include "LTexture.h"
#include "Game.h"

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = mHeight = 0;
}

void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = mHeight = 0;
	}
}

LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile(string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
		mTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);
		if (mTexture) {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return mTexture != NULL;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(float x, float y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(Game::gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}