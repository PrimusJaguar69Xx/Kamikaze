#include "Game_Controller.h"


Game_Controller::Game_Controller() {
	window = nullptr;
	windowSurface = nullptr;
}

int Game_Controller::Init(int windowW, int windowH) {
	int iResult = 0;

	iResult = SDL_Init(SDL_INIT_VIDEO);
	if (iResult < 0) {
		return -1;
	}

	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("KAMIKAZE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, NULL);
	if (window == NULL) {
		return -1;
	}

//	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (iResult < 0) {
		printf("error setting window to fullscreen");
		exit(-1);
	}
	iResult = SDL_SetRenderDrawColor(renderer, 0xFF, 0xAF, 0xFF, 0xAF);
	if (iResult < 0) {
		printf("error settng renderdrawcolor()");
		exit(-1);
	}

	return 0;
}

Game_Controller::~Game_Controller() {
	SDL_FreeSurface(windowSurface);
	windowSurface = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;
}

void Game_Controller::LoadLevel(bool bCurrLvl, Level_Template* lvl) {
	if (bCurrLvl) {
		currLvl->Unload();
	}
	currLvl = lvl;
	currLvl->Load(renderer);
}
void Game_Controller::UnloadLevel() {
	currLvl->Unload();
	currLvl = nullptr;
}