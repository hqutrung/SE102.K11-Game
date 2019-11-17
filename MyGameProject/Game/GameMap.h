#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <vector>
#include <unordered_map>
#include "demoEnemy.h"
#include "Grid.h"
#include "Unit.h"
#include <iostream>
#include <fstream>

class Tileset {
	int tileWidth;
	int tileHeight;
	int rows;
	int columns;
	std::unordered_map<int, LPSPRITE> tiles;
public:
	Tileset(int rows, int columns, int tileWidth, int tileHeight);
	void Add(int id, LPSPRITE tile);
	int GetRows();
	int GetColumns();
	int GetTileWidth();
	int GetTileHeight();
	LPSPRITE GetSprite(int id);
};

class GameMap
{
private:
	Grid* grid;
	Camera* Cam;
	Tileset* tileset;
	LPCSTR mapPath;
	int rows;
	int columns;
	int mapObjects;
	int** mapIDs;
public:
	GameMap(char* tilesetPath, char* mapPath, int tileHeight = 16, int tileWidth = 16, bool gridBuildIn = false);
	void LoadTileset(char* filePath, int tileWidth, int tileHeight);
	void SetMapPath(char* mapPath);

	bool isContain(BoxCollider rect1, BoxCollider rect2);

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	int GetRows();
	int GetColumns();

	void SetCamera(Camera* cam);

	Grid* GetGrid();

	void Draw();

	~GameMap();
};

#endif

