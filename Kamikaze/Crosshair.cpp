#include "Crosshair.h"

Crosshair::Crosshair(char* path, SDL_Renderer* render, int distFromSprite, double* x, double* y, double* rot, SDL_Point* spriteCenter) {
	texture = new Resource_Texture(path, render);

	distanceFromSprite = distFromSprite;

	spritePos.spriteRot = rot;
	spritePos.spriteX = x;
	spritePos.spriteY = y;

	this->crosshairCenter = *spriteCenter;
	
}

void Crosshair::UpdatePos() {
	crosshairPos.spriteRot = *spritePos.spriteRot;
	crosshairPos.spriteX = cos((crosshairPos.spriteRot - 90) * 0.0174533) * distanceFromSprite + *spritePos.spriteX + crosshairCenter.x - texture->GetWidth()/2;
	crosshairPos.spriteY = sin((crosshairPos.spriteRot - 90) * 0.0174533) * distanceFromSprite + *spritePos.spriteY + crosshairCenter.y - texture->GetHeight()/2;
}

void Crosshair::Render() {
//	texture->RenderTexture(*spritePos.spriteX + spriteCenter->x, *spritePos.spriteY + spriteCenter->y + distanceFromSprite, NULL, *spritePos.spriteRot, NULL, SDL_FLIP_NONE);
	texture->RenderTexture(crosshairPos.spriteX, crosshairPos.spriteY, NULL, *spritePos.spriteRot, NULL, SDL_FLIP_NONE);
}