#pragma once

#include "Resource_Texture.h"

#include <fstream>

#define MAP_MAX_TILES_X 40
#define MAP_MAX_TILES_Y 24

#define TILES_MAX 12


typedef struct {
	int x;
	int y;
	int type;
}Tile;

class MapTiles {
	Resource_Texture* tileset;
	SDL_Rect Tiles[TILES_MAX];
	SDL_Rect Hitboxes[MAP_MAX_TILES_X * MAP_MAX_TILES_Y];

	Tile TilesPosOnMap[MAP_MAX_TILES_X * MAP_MAX_TILES_Y];

	int nTiles;
	int tileSize;

	int nTilesOnMap;
public:
	MapTiles(SDL_Renderer* render, char* path);

	void InitTiles(int tileSize, int nTilesX, int nTilesY);
	void LoadMap(int mapTilesX, int mapTilesY, char* path, bool hitboxes);
	void renderTiles();

	int GetNTilesOnMap() {
		return nTilesOnMap;
	}

	SDL_Rect GetIHitbox(int i) {
		return Hitboxes[i];
	}
};