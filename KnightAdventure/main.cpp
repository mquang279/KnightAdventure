#include "Game.h"
#include <string>

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	Uint32 frameStart;
	int frameTime;
	
	game = new Game();
	game->init("Knight Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 640, false);
	game->loadMedia();
	while (game->running()) {
		frameStart = SDL_GetTicks();
		
		game->handleEvent();
		game->update();
		game->render();
		
		frameTime =	SDL_GetTicks() - frameStart;

		if (1000 / FPS > frameTime) {
			SDL_Delay((1000 / FPS) - frameTime);
		}
	}
	game->close();
	return 0;
}