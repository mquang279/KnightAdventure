#include "Game.h"

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
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();
		
		deltaTime = (SDL_GetTicks() - frameStart) * (FPS / 1000.0f);

		if (deltaTime > TARGET_DELTATIME) {
			deltaTime = TARGET_DELTATIME;
		}
		/*frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}*/
	}
	game->close();
	return 0;
}