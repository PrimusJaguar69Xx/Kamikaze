#pragma once

#include <SDL2\SDL.h>
#include <vector>

#include "Resource_Texture.h"
#include "Sprite.h"

#define EFFECT_UPDATERATE 4


class Effect {

	Resource_Texture* texture;

	std::vector<SDL_Rect> sourceRects;

	std::vector<XYRot> pos;

	std::vector<int> frame;

	int nFrames;
	int nEffects;

public:

	Effect(char* path, SDL_Renderer* render, int nFrames, int frameSize);

	void NewEffect(XYRot pos);
	void DeleteEffect(int effectNum);
	void NextFrame(int effectNum);
	void RenderEffects();

	int GetNEffect() {
		return nEffects;
	}

};