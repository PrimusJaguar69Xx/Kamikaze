#pragma once

#include "Resource_Texture.h"
#include "SDL2\SDL.h"

#define MAX_ANIMATIONS 16
#define MAX_FRAMES 8


#define MAX_HIT_DISTANCE 1920

enum hitObject {
	HITOBJECT_OBSTACLE,
	HITOBJECT_SPRITE,
	HITOBJECT_NULL
};

typedef struct {
	hitObject Object;
	int nObject;
	SDL_Point pointOfImpact;
	double angle;
} hitInfo;


typedef struct {
	int aniN;
	int nFrames;
} State;

struct spriteStrip {
	SDL_Rect sprites[MAX_FRAMES];
};

typedef struct {
	double spriteRot;
	double spriteX;
	double spriteY;
	double xDir;
	double yDir;
}XYRotDir;

typedef struct {
	double spriteRot;
	double spriteX;
	double spriteY;
} XYRot;

class Sprite {
	int nSprite;

	Resource_Texture* texture;
	SDL_Renderer* renderer;
	spriteStrip spriteSheet[MAX_ANIMATIONS];
	
	XYRotDir spritePos;
	State state;
	SDL_Point localCenter;
	
	SDL_Rect hitbox;
	int xOffset;
	int yOffset;


	
public:
	Sprite(SDL_Renderer* render);
	~Sprite();

	void InitSprite(char filepath[]);
	void CreateSpriteSheet(int spriteHeight, int spriteWidth, int rows, int collums);

	void SetSpriteN(int n) {
		nSprite = n;
	}

	void UpdateHitbox() {
		hitbox.x = xOffset + spritePos.spriteX;
		hitbox.y = yOffset + spritePos.spriteY;
	}

	spriteStrip getAnimation(int n) {
		return spriteSheet[n];
	}

	Resource_Texture* GetTexture() {
		return texture;
	}

	XYRotDir GetPos() {
		return spritePos;
	}

	void ChangePos(double spriteRot, double spriteX, double spriteY) {
		spritePos.spriteRot = spriteRot;
		spritePos.spriteX = spriteX;
		spritePos.spriteY = spriteY;
	}

	void SetState(int aniN, int nFrame) {
		if (aniN > MAX_ANIMATIONS) printf("call to state failed, to high a number");
		state.aniN = aniN;
		state.nFrames = nFrame;
	}

	State GetState() {
		return state;
	}

	void SetCenter(int x, int y) {
		localCenter.x = x;
		localCenter.y = y;
	}
	SDL_Point* GetCenter() {
		return &localCenter;
	}

	SDL_Rect GetHitbox() {
		return hitbox;
	}

	double* GetXPointer() {
		return &spritePos.spriteX;
	}

	double* GetYPointer() {
		return &spritePos.spriteY;
	}

	double* GetRotPointer() {
		return &spritePos.spriteRot;
	}

	void RenderSprite(int nFrame, int updateRate);

	void CreateCustomHitbox(int offsetFromX, int offsetFromY, int height, int width);

	hitInfo CheckLineOfFire(SDL_Rect targetHitbox, SDL_Rect* obstacles, int nObstacles, int xOffset, int yOffset);

	bool CheckCollision(SDL_Rect collisionObject, int xSpritePosOff = NULL, int ySpritePosOff = NULL);
	bool CheckCollision(SDL_Rect collisionObject[], bool sprite, int nObjects, int xSpritePosOff = NULL, int ySpritePosOff = NULL);
};