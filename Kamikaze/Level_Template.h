#pragma once

#include "SDL2\SDL.h"

class Level_Template {
public:
	virtual void Load(SDL_Renderer* render) = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};