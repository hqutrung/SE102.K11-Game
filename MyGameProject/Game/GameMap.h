#pragma once
#include <iostream>
#include <fstream>
#include "Sprites.h"

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

class GameMap {
public:
	GameMap(LPCWSTR tilesetPath, LPCWSTR mapPath, int tileHeight = 32, int tileWidth = 32, bool gridBuildIn = false);
	void SetMapPath(LPCWSTR mapPath);
	void SetMapPathGridBuildIn(LPCWSTR mapPath);
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void Draw();
	//Active objects
	//void GetStaticObjects(std::vector<Entity*> &entities);
	~GameMap();
private:

	void LoadTileset(LPCWSTR filePath, int tileWidth, int tileHeight);
	Tileset* tileset;
	LPCWSTR mapPath;
	int rows;
	int columns;
	int mapObject;
	int** mapIDs;
	std::unordered_map<int, LPSPRITE> listTileset;

};