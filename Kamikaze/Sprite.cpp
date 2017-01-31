#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* render) {
	texture = nullptr;
	renderer = render;


	spritePos.spriteRot = 0;
	spritePos.spriteX = 0;
	spritePos.spriteY = 0;

	xOffset = 0;
	yOffset = 0;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture->Get_Texture());
}

void Sprite::InitSprite(char filepath[]) {
	texture = new Resource_Texture(filepath, renderer);
	hitbox.w = texture->GetWidth();
	hitbox.h = texture->GetHeight();
}

void Sprite::CreateSpriteSheet(int spriteHeight, int spriteWidth, int rows, int collums) {
	for (int i = 0; i < rows; i++) {
		for (int ii = 0; ii < collums; ii++) {
			spriteSheet[i].sprites[ii].h = spriteHeight;
			spriteSheet[i].sprites[ii].w = spriteWidth;
			spriteSheet[i].sprites[ii].x = ii*spriteWidth;
			spriteSheet[i].sprites[ii].y = i*spriteHeight;
		} 
	}
}

void Sprite::CreateCustomHitbox(int offsetFromX, int offsetFromY, int height, int width) {
	xOffset = offsetFromX;
	yOffset = offsetFromY;
	hitbox.w = width;
	hitbox.h = height;
}

bool Sprite::CheckCollision(SDL_Rect collisionObject, int xSpritePosOff, int ySpritePosOff) {
	hitbox.x = xOffset + spritePos.spriteX + xSpritePosOff;
	hitbox.y = yOffset + spritePos.spriteY + ySpritePosOff;

	int hitboxLeft = hitbox.x;
	int hitboxTop = hitbox.y;
	int hitboxRight = hitbox.x + hitbox.w;
	int hitboxBottom = hitbox.y + hitbox.h;
//	printf("left: %d \ntop: %d \nright: %d \nbottom: %d \n\n", hitboxLeft, hitboxTop, hitboxRight, hitboxBottom);

	int collisionObjectLeft = collisionObject.x;
	int collisionObjectTop = collisionObject.y;
	int collisionObjectRight = collisionObject.x + collisionObject.w;
	int collisionObjectBottom = collisionObject.y + collisionObject.h;
//	printf("left: %d \ntop: %d \nright: %d \nbottom: %d \n\n", collisionObjectLeft, collisionObjectTop, collisionObjectRight, collisionObjectBottom);


	if (hitboxLeft > collisionObjectRight)
		return false;

	if (hitboxTop > collisionObjectBottom)
		return false;

	if (hitboxRight < collisionObjectLeft)
		return false;

	if (hitboxBottom < collisionObjectTop)
		return false;

	return true;

}


bool Sprite::CheckCollision(SDL_Rect collisionObject[], bool sprite, int nObjects, int xSpritePosOff, int ySpritePosOff) {
	hitbox.x = xOffset + spritePos.spriteX + xSpritePosOff;
	hitbox.y = yOffset + spritePos.spriteY + ySpritePosOff;

	int hitboxLeft = hitbox.x;
	int hitboxTop = hitbox.y;
	int hitboxRight = hitbox.x + hitbox.w;
	int hitboxBottom = hitbox.y + hitbox.h;
	//	printf("left: %d \ntop: %d \nright: %d \nbottom: %d \n\n", hitboxLeft, hitboxTop, hitboxRight, hitboxBottom);

	for (int i = 0; i <= nObjects; i++) {
		if (i == nObjects) {
			return false;
		}
		if (sprite && i == nSprite) continue;

		
		int collisionObjectLeft = collisionObject[i].x;
		int collisionObjectTop = collisionObject[i].y;
		int collisionObjectRight = collisionObject[i].x + collisionObject[i].w;
		int collisionObjectBottom = collisionObject[i].y + collisionObject[i].h;
		//	printf("left: %d \ntop: %d \nright: %d \nbottom: %d \n\n", collisionObjectLeft, collisionObjectTop, collisionObjectRight, collisionObjectBottom);


		if (hitboxLeft > collisionObjectRight)
			continue;

		if (hitboxTop > collisionObjectBottom)
			continue;

		if (hitboxRight < collisionObjectLeft)
			continue;

		if (hitboxBottom < collisionObjectTop)
			continue;

		return true;
	}
}

hitInfo Sprite::CheckLineOfFire(SDL_Rect targetHitbox, SDL_Rect* obstacles, int nObstacles, int xOffset, int yOffset) {
	
	hitInfo info;
	
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	printf("x: %d, y: %d\n", mouseX, mouseY);

	int offsetX = xOffset - localCenter.x;
	int offsetY = localCenter.y - yOffset;

	int rot = spritePos.spriteRot;
	info.angle = rot;

	double x = spritePos.spriteX + localCenter.x;
	double y = spritePos.spriteY + localCenter.y;

	int collisionObjectLeft = targetHitbox.x;
	int collisionObjectTop = targetHitbox.y;
	int collisionObjectRight = targetHitbox.x + targetHitbox.w;
	int collisionObjectBottom = targetHitbox.y + targetHitbox.h;
		//	printf("left: %d \ntop: %d \nright: %d \nbottom: %d \n\n", collisionObjectLeft, collisionObjectTop, collisionObjectRight, collisionObjectBottom);

	for (int i = 0; i < MAX_HIT_DISTANCE; i++) {
		for (int i = 0; i < nObstacles; i++) {
				if (i == nObstacles) {
					break;
				}

				int collisionObjectLeftO = obstacles[i].x;
				int collisionObjectTopO = obstacles[i].y;
				int collisionObjectRightO = obstacles[i].x + obstacles[i].w;
				int collisionObjectBottomO = obstacles[i].y + obstacles[i].h;
				//	printf("left: %d \ntop: %d \nright: %d \nbottom: %d \n\n", collisionObjectLeft, collisionObjectTop, collisionObjectRight, collisionObjectBottom);


				if (x > collisionObjectRightO)
					continue;

				if (y > collisionObjectBottomO)
					continue;

				if (x < collisionObjectLeftO)
					continue;

				if (y < collisionObjectTopO)
					continue;


				info.Object = HITOBJECT_OBSTACLE;
				info.pointOfImpact.x = x;
				info.pointOfImpact.y = y;
				info.nObject = i;
				return info;
			}

		x += cos((rot-90) * 0.0174533);
		y += sin((rot-90) * 0.0174533);
		
		if (x > collisionObjectRight)
			continue;

		if (y > collisionObjectBottom)
			continue;

		if (x < collisionObjectLeft)
			continue;

		if (y < collisionObjectTop)
			continue;

		if (!(y < collisionObjectTop) && !(x < collisionObjectLeft) && !(y > collisionObjectBottom) && !(x > collisionObjectRight))
			info.Object = HITOBJECT_SPRITE;
			info.pointOfImpact.x = x;
			info.pointOfImpact.y = y;
			info.nObject = i;
			return info;
	}

	info.Object = HITOBJECT_NULL;
	info.pointOfImpact.x = NULL;
	info.pointOfImpact.y = NULL;
	info.nObject = NULL;
	return info;
}

void Sprite::RenderSprite(int nFrame, int updateRate) {
	texture->RenderTexture(spritePos.spriteX, spritePos.spriteY, &spriteSheet[state.aniN].sprites[nFrame / updateRate], spritePos.spriteRot, &localCenter, SDL_FLIP_NONE);
	SDL_RenderDrawRect(renderer, &hitbox);
}