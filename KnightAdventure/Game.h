#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cstdlib>


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
	void loadMedia();
	void handleEvent();
	void update();
	void render();
	void close();
	void reload();
	bool running();
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	static SDL_Renderer* gRenderer;
private:
	SDL_Event e;
	const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 640;
	bool isRunning;
	SDL_Window* gWindow;
};

