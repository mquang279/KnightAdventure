#include "Game.h"
#include <string>

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const float TARGET_DELTATIME = 1.5f;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	float deltaTime;
	
	game = new Game();
	game->init("Knight Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 640, false);
	game->loadMedia();
	while (game->running()) {
		game->handleEvent();
		game->update();
		game->render();
		/*frameStart = SDL_GetTicks();
		deltaTime = (SDL_GetTicks() - frameStart) * (FPS / 1000.0f);

		if (deltaTime > TARGET_DELTATIME) {
			deltaTime = TARGET_DELTATIME;
		}*/
	}
	game->close();
	return 0;
}