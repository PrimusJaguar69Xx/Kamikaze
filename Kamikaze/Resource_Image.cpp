#include "Resource_Image.h"

Resource_Image::Resource_Image(char path[]) {
	Image = NULL;
	SDL_Surface* Loaded_Image = SDL_LoadBMP(path);
	if (Loaded_Image == NULL) {
		printf("error couldnt load image, error: %s", SDL_GetError());
	}

	Image = SDL_ConvertSurface(Loaded_Image, Loaded_Image->format, NULL);
	if (Image == NULL) {
		printf("error couldnt load image, error: %s", SDL_GetError());
	}

	SDL_FreeSurface(Loaded_Image);
}

Resource_Image::~Resource_Image() {
	SDL_FreeSurface(Image);
}