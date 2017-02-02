#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <stdlib.h>

#include "Sprite.h"


class Timer {
	TTF_Font* font;
	SDL_Color color;
	
	double startTime;
	double currTime;
	int destTime;

	int min;
	int sec;

	char cSec[2];
	char cMin[2];
	char text[8];

	SDL_Renderer* render;

	SDL_Rect destRect;

public:

	Timer(int time, char* pathToTff, int x, int y, int h, int w, int points, SDL_Color c, SDL_Renderer* renderer);
	void StartTimer();
	void RenderTimer();
};