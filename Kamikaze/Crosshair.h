#pragma once

#include "Resource_Texture.h"
#include "Sprite.h"

typedef struct {
	double* spriteX;
	double* spriteY;
	double* spriteRot;


} XYRotPointer;

class Crosshair {

	int distanceFromSprite;

	Resource_Texture* texture;
	XYRotPointer spritePos;
	XYRot crosshairPos;
	SDL_Point crosshairCenter;

public:
	Crosshair(char* path, SDL_Renderer* render, int distFromSprite, double* x, double* y, double* rot, SDL_Point* spriteCenter);

	void UpdatePos();
	void Render();
};