#include "MapTiles.h"

MapTiles::MapTiles(SDL_Renderer* render, char* path) {
	tileset = new Resource_Texture(path, render);
	nTilesOnMap = 0;
}


void MapTiles::InitTiles(int tileSize, int nTilesX, int nTilesY) {
	this->tileSize = tileSize;
	
	int x = 0;
	int y = 0;
	
	for (int i = 0; i < nTilesX * nTilesX; i++) {
		Tiles[i].h = tileSize;
		Tiles[i].w = tileSize;
		Tiles[i].x = x;
		Tiles[i].y = y;

		x += tileSize;

		if (x >= nTilesX * tileSize) {
			x = 0;
			y += tileSize;
		}
	}
}
void MapTiles::LoadMap(int mapTilesX, int mapTilesY, char* path, bool bHitboxes) {
	nTilesOnMap = mapTilesX * mapTilesY;
	
	int x = 0;
	int y = 0;
	
	std::fstream map(path);

	for (int i = 0; i < mapTilesX * mapTilesY; i++) {
		int type = -1;
		map >> type;

		
			TilesPosOnMap[i].type = type;
			TilesPosOnMap[i].x = x;
			TilesPosOnMap[i].y = y;
			if (bHitboxes && TilesPosOnMap[i].type != -1) {
				Hitboxes[i].h = tileSize;
				Hitboxes[i].w = tileSize;
				Hitboxes[i].x = x;
				Hitboxes[i].y = y;
			}
		
		
		x += tileSize;

		if (x >= mapTilesX * tileSize) {
			x = 0;
			y += tileSize;
		}
	}

}

void MapTiles::renderTiles() {
	for (int i = 0; i < nTilesOnMap; i++) {
		if (TilesPosOnMap[i].type != -1)
			tileset->RenderTexture(TilesPosOnMap[i].x, TilesPosOnMap[i].y, &Tiles[TilesPosOnMap[i].type]);
	}
}