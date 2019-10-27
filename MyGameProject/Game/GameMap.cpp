#include "GameMap.h"
#include "Textures.h"

Tileset::Tileset(int rows, int columns, int tileWidth, int tileHeight) {
	this->rows = rows;
	this->columns = columns;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
}

void Tileset::Add(int id, LPSPRITE tile) {
	tiles[id] = tile;
}

int Tileset::GetRows() {
	return rows;
}

int Tileset::GetColumns() {
	return columns;
}

int Tileset::GetTileWidth() {
	return tileWidth;
}

int Tileset::GetTileHeight() {
	return tileHeight;
}

LPSPRITE Tileset::GetSprite(int id) {
	return tiles[id];
}
//GameMap::GameMap() {
//	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();
//	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
//	grid = new Grid(MyHelper::ToRect(0, bufferWidth, 0, bufferHeight), 1, 1);
//}
//
//GameMap::GameMap(char * tilesetPath, int tileWidth, int tileHeight) {
//}

GameMap::GameMap(LPCSTR tilesetPath, LPCSTR mapPath, int tileHeight, int tileWidth, bool gridBuildIn) {
	LoadTileset(tilesetPath, tileWidth, tileHeight);
	if (gridBuildIn)
		SetMapPathGridBuildIn(mapPath);
	else
		SetMapPath(mapPath);
}

void GameMap::SetMapPath(LPCSTR mapPath) {
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}
	reader >> rows;
	reader >> columns;
	mapIDs = new int*[rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}
}

void GameMap::SetMapPathGridBuildIn(LPCSTR mapPath) {
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}
	reader >> rows;
	reader >> columns;
	mapIDs = new int*[rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}
}

int GameMap::GetWidth() {
	return tileset->GetTileWidth() * columns;
}

int GameMap::GetHeight() {
	return tileset->GetTileHeight() * rows;
}

int GameMap::GetTileWidth() {
	return tileset->GetTileWidth();
}

int GameMap::GetTileHeight() {
	return tileset->GetTileHeight();
}


void GameMap::Draw() {

	for (size_t i = 0; i < 1; i++) {

		//chieu dai va chieu rong cua tile
		int tileWidth = tileset->GetTileWidth();
		int tileHeight = tileset->GetTileHeight();

		for (int m = 0; m < this->rows; m++) {
			for (int n = 0; n < this->columns; n++) {
				int id = mapIDs[m][n];

				LPSPRITE sprite = tileset->GetSprite(id);

				D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);
				sprite->SetHeight(tileHeight);
				sprite->SetWidth(tileWidth);
				sprite->Draw(position, BoxCollider());
			}
		}
	}

}

GameMap::~GameMap() {
	delete tileset;
	tileset = NULL;
	for (int m = 0; m < this->rows; m++) {
		delete mapIDs[m];
		mapIDs[m] = NULL;
	}
	delete mapIDs;
	mapIDs = NULL;
}

void GameMap::LoadTileset(LPCSTR filePath, int tileWidth, int tileHeight) {
	//Parse map tu file 
	Textures::GetInstance()->Add(11, filePath, D3DCOLOR_XRGB(255, 0, 255));
	auto texture = Textures::GetInstance()->GetTexture(11);
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	auto width = desc.Width;
	auto height = desc.Height;
	tileset = new Tileset(height / tileHeight, width / tileWidth, tileWidth, tileHeight);

	for (int i = 0; i < tileset->GetRows(); i++) {
		for (int j = 0; j < tileset->GetColumns(); j++) {
			BoxCollider r;
			r.top = i * tileHeight;
			r.left = j * tileWidth;
			r.bottom = r.top + tileHeight;
			r.right = r.left + tileWidth;
			LPSPRITE sprite = new Sprites(texture, r);
			tileset->Add(i * tileset->GetColumns() + j, sprite);
		}
	}
}

