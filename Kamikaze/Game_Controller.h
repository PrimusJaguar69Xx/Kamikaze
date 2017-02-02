#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "Level_Template.h"
#include <stdio.h>
#include <SDL2\SDL_ttf.h>

class Game_Controller {
	SDL_Window* window;
	SDL_Surface* windowSurface;

	SDL_Renderer* renderer;
	Level_Template* currLvl;

public:
	Game_Controller();
	~Game_Controller();

	int Init(int windowW, int windowH);

	void LoadLevel(bool bCurrLvl, Level_Template* lvl);
	void UnloadLevel();

	SDL_Window* GetWindow() {
		return window;
	}

	SDL_Surface* GetSurface() {
		return windowSurface;
	}

	SDL_Renderer* GetRenderer() {
		return renderer;
	}

	Level_Template* GetCurrLvl() {
		return currLvl;
	}
};