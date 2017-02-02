#pragma once

#include "Level_Template.h"
#include "Sprite.h"
#include "SDL2\SDL.h"
#include "MapTiles.h"
#include <math.h>
#include "Object.h"
#include "Crosshair.h"
#include "Effect.h"
#include <vector>
#include "Timer.h"

#define SPRITE_VEL 3
#define SPRITE_SEC_VEL 2
#define SPRITE_ROT_VEL 2
#define SPRITE_MAX 6

#define SPRITE_UPDATERATE 12

#define SPRITE_EFFECT_UPDATERATE 3

#define OBJECTS_MAX 512

#define EFFECTS_MAX 4


class Default_Level: public Level_Template {

	Timer* timer;

	int soliderFrame;
	Sprite* solider;

	Effect* hitObjectEffect;
	Effect* hitSpriteEffect;

	std::vector<Sprite*> spriteList;

	Sprite* solider2;
	int TargetFrame;

	Sprite* solider_effects;
	Sprite* solider2_effects;

	Object* boxes;
	Object* boxes2;
	Object* boxes3;

	Object* barrel;
	Object* barrel2;


	MapTiles* background;
	MapTiles* walls;

	SDL_Rect objects[OBJECTS_MAX];
	int nObjects;

//	SDL_Rect sprites[SPRITE_MAX];
//	int nSprite;
	
	Crosshair* crosshair;

	SDL_Renderer* renderer;

	const Uint8* LastKeyStates;

public:
	void Load(SDL_Renderer* render) override;
	void Unload() override;
	void Update() override;
	void Render() override;
};