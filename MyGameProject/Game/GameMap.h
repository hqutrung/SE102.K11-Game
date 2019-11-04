#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <vector>

#include "MapReader/Tmx.h.in"
#include "demoEnemy.h"
#include "Grid.h"
#include "Unit.h"

class GameMap
{
	Grid* grid;
	Tmx::Map* mMap;
	std::map<int, Sprites*>          mListTileset;
	Camera* Cam;
public:
	GameMap(char* filePath);
	void LoadMap(char* filePath);
	Tmx::Map* GetMap();
	void SetMapGrid();

	bool isContain(BoxCollider rect1, BoxCollider rect2);

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void SetCamera(Camera* cam);

	Grid* GetGrid();

	void Draw();

	~GameMap();
};

#endif

