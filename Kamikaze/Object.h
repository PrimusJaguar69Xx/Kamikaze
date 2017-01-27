#pragma once

#include <SDL2\SDL.h>
#include "Resource_Texture.h"


class Object {
	Resource_Texture* texture;

	SDL_Rect hitbox;

	int xOffset;
	int yOffset;

	int x;
	int y;

public:
	Object(char* path, SDL_Renderer* render, int x, int y);

	void RenderObject();

	void CreateCustomHitbox(int offsetFromX, int offsetFromY, int height, int width);

	SDL_Rect GetHitbox() {
		return hitbox;
	}
};