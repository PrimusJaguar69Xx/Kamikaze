#include "Object.h"

Object::Object(char* path, SDL_Renderer* render, int x, int y) {
	texture = new Resource_Texture(path, render);

	xOffset = 0;
	yOffset = 0;

	hitbox.w = texture->GetWidth();
	hitbox.h = texture->GetWidth();
	hitbox.x = x;
	hitbox.y = y;

	this->x = x;
	this->y = y;
}

void Object::RenderObject() {
	texture->RenderTexture(x, y, NULL);
}

void Object::CreateCustomHitbox(int offsetFromX, int offsetFromY, int height, int width) {
	xOffset = offsetFromX;
	yOffset = offsetFromY;
	hitbox.w = width;
	hitbox.h = height;
}