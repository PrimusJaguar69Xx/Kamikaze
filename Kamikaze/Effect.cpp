#include "Effect.h"

Effect::Effect(char* path, SDL_Renderer* render, int nFrames, int frameSize) {
	this->nFrames = nFrames;
	
	texture = new Resource_Texture(path, render);

	for(int i = 0; i < nFrames; i++){
		SDL_Rect temp;
		temp.h = frameSize;
		temp.w = frameSize;
		temp.x = i * frameSize;
		temp.y = 0;
		
		sourceRects.push_back(temp);
	}
	pos.reserve(sizeof(XYRot) * 4);

	nEffects = 0;

	center.x = frameSize / 2;
	center.y = frameSize / 2;
}

void Effect::NewEffect(XYRot pos) {
	this->pos.push_back(XYRot());
	this->pos[nEffects] = pos;
	frame.push_back(0);
	nEffects++;
}

void Effect::DeleteEffect(int effectNum) {
	this->pos.erase(pos.begin() + effectNum);
	frame.erase(frame.begin() + effectNum);
	nEffects--;
}

void Effect::NextFrame(int effectNum) {
	frame[effectNum] += 1;
	if (frame[effectNum] / EFFECT_UPDATERATE >= nFrames)
		DeleteEffect(effectNum);
} 

void Effect::RenderEffects(SDL_Renderer* render) {
	for (unsigned int i = 0; i < nEffects; i++) {
		texture->RenderTexture(pos[i].spriteX - center.x, pos[i].spriteY - center.y, &sourceRects[frame[i] / EFFECT_UPDATERATE], pos[i].spriteRot, &center, SDL_FLIP_NONE);
		SDL_RenderDrawPoint(render, pos[i].spriteX + center.x, pos[i].spriteY + center.y);
	}
}