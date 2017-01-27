#pragma once

#include <SDL2\SDL.h>
#include <stdio.h>

int Error(int n = 0) {
	printf("An error occured: %d", n);
	exit(n);
}

int Error(int n, SDL_Window* window = NULL) {
	printf("An error occured: %d, %s", n, SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(n);
}