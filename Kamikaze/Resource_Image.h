#pragma once

#include "SDL2\SDL.h"
#include <stdio.h>

//obselete
class Resource_Image {
	SDL_Surface* Image;
public:
	Resource_Image(char path[]);

	~Resource_Image();

	SDL_Surface* GetImage() {
		return Image;
	}

};