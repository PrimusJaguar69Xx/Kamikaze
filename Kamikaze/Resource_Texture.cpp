#include "Resource_Texture.h"


Resource_Texture::Resource_Texture(char path[], SDL_Renderer* renderer) {
	localRenderer = renderer;
	Texture = NULL;
	SDL_Surface* Loaded_Image = NULL;

	Loaded_Image = IMG_Load(path);
	if (Loaded_Image == NULL) {
		printf("error couldnt load image, error: %s", SDL_GetError());
	}

	Texture = SDL_CreateTextureFromSurface(renderer, Loaded_Image);
	if (Texture == NULL) {
		printf("error couldnt load image, error: %s", SDL_GetError());
	}

	width = Loaded_Image->w;
	height = Loaded_Image->h;

	SDL_FreeSurface(Loaded_Image);
}

void Resource_Texture::RenderTexture(int x, int y, SDL_Rect* sourceRect) {
	SDL_Rect destRect = { x, y, width, height };

	if (sourceRect != nullptr) {
		destRect.h = sourceRect->h;
		destRect.w = sourceRect->w;
	}

	SDL_RenderCopy(localRenderer, Texture, sourceRect, &destRect);
}

void Resource_Texture::RenderTexture(int x, int y, SDL_Rect* sourceRect, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect destRect = { x, y, width, height };

	if (sourceRect != nullptr) {
		destRect.h = sourceRect->h;
		destRect.w = sourceRect->w;
	}

	SDL_RenderCopyEx(localRenderer, Texture, sourceRect, &destRect, angle, center, flip);
}

Resource_Texture::~Resource_Texture() {
	SDL_DestroyTexture(Texture);
}