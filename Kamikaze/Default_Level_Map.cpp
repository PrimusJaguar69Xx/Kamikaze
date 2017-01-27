#include "Default_Level_Map.h"

Default_Level_Map::Default_Level_Map() {
	tileset = new Tileset();
}

void Default_Level_Map::LoadTileset(char* path, SDL_Renderer* render, int rows, int collums, int tileSize) {
	tileset->LoadTileset(path, render);
	tileset->CreateTileset(tileSize, rows, collums);
}

void Default_Level_Map::CreateMap() {
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int ii = 0; ii < MAP_HEIGHT; ii++) {
			lvl1[i][ii].x = tileset->GetTilesetRects()[1].tiles[1].x;
			lvl1[i][ii].y = tileset->GetTilesetRects()[1].tiles[1].y;
		}
	}
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int ii = 0; ii < MAP_HEIGHT; ii++) {
			if (i == 0 && ii == 0) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[0].tiles[0].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[0].tiles[0].y;
			}
			else if (i == MAP_WIDTH && ii == 0) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[2].tiles[0].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[2].tiles[0].y;
			}
			else if (i == 0 && ii == MAP_HEIGHT) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[0].tiles[2].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[0].tiles[2].y;
			}
			else if (i == MAP_WIDTH && ii == MAP_HEIGHT) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[2].tiles[2].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[2].tiles[2].y;
			}

			else if (ii == 0) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[1].tiles[0].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[1].tiles[0].y;
			}

			else if (i == 0) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[0].tiles[1].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[0].tiles[1].y;
			}

			else if (ii == MAP_HEIGHT) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[1].tiles[2].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[1].tiles[2].y;
			}

			else if (i == MAP_WIDTH) {
				lvl2[i][ii].x = tileset->GetTilesetRects()[2].tiles[1].x;
				lvl2[i][ii].y = tileset->GetTilesetRects()[2].tiles[1].y;
			}
		}
	}

}

void Default_Level_Map::RenderLevel1() {
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int ii = 0; ii < MAP_HEIGHT; ii++) {
			tileset->GetTexture()->RenderTexture(16*i, 16*ii, &tileset->GetTilesetRects()[lvl1[i][ii].x].tiles[lvl1[i][ii].y]);
		}
	}

//	tileset->GetTexture()->RenderTexture(0, 0, NULL);
}