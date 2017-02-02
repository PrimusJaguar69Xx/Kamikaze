#include "Timer.h"

Timer::Timer(int timeSecs, char* pathToTff, int x, int y, int h, int w, int points, SDL_Color c, SDL_Renderer* renderer) {
	font = TTF_OpenFont(pathToTff, points);
	if (font == NULL) {
		printf("error loading font file: %s\n", SDL_GetError);
	}
	color = c;	

	destTime = timeSecs * 1000;

	render = renderer;

	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;
}

void Timer::StartTimer() {
	startTime = SDL_GetTicks();
	destTime += SDL_GetTicks();
}

void Timer::RenderTimer() {
	currTime = SDL_GetTicks();
	min = ((int)currTime - (int)startTime) / 1000 / 60;
	sec = ((int)currTime - (int)startTime) / 1000 % 60;

	itoa(min, cMin, 10);
	itoa(sec, cSec, 10);

	SDL_memset(&text, 0, sizeof(text));

	text[0] = '2';//cMin[0];
	text[1] = '2';//cMin[1];
	text[2] = ' ';
	text[3] = ':';
	text[4] = ' ';
	text[5] = '2';//cSec[0];
	text[6] = '2';//cSec[1];
	text[7] = '\0';

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);

	SDL_RenderCopy(render, texture, NULL, &destRect);

}
