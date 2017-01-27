#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>



class Resource_Texture {
	SDL_Texture* Texture;
	int height;
	int width;

	SDL_Renderer* localRenderer;

public:
	Resource_Texture(char path[], SDL_Renderer* renderer);
	~Resource_Texture();

	void RenderTexture(int x, int y, SDL_Rect* sourceRect);
	void RenderTexture(int x, int y, SDL_Rect* sourceRect, double angle, SDL_Point* center, SDL_RendererFlip flip);

	SDL_Texture* Get_Texture() {
		return Texture;
	}

	int GetHeight() {
		return height;
	}
	
	int GetWidth() {
		return width;
	}
};