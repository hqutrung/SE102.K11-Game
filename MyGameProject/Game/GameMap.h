#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprites.h"
#include "MapReader/Tmx.h.in"
#include "Graphic.h"
#include "Camera.h"
#include "Textures.h"

class GameMap
{
public:
	GameMap(char* filePath);

	Tmx::Map* GetMap();

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void SetCamera(Camera* cam);

	void Draw();

	~GameMap();

private:
	void LoadMap(char* filePath);

	bool isContain(BoxCollider rect1, BoxCollider rect2);

	Tmx::Map* mMap;
	std::map<int, Sprites*>          mListTileset;
	Camera* Cam;
};

#endif

