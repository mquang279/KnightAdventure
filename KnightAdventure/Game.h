#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvent();
	void update();
	void render();
	void close();
	bool running();
	static SDL_Renderer* gRenderer;
private:
	const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 640;
	bool isRunning;
	SDL_Window* gWindow;
};

