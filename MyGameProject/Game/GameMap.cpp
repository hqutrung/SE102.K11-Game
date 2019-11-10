#include "GameMap.h"

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

GameMap::GameMap(char* tilesetPath, char* mapPath, int tileHeight , int tileWidth, bool gridBuildIn)
{
	LoadTileset(tilesetPath, tileWidth, tileHeight);
	if (gridBuildIn)
		SetMapPathGridBuildIn(mapPath);
	else
		SetMapPath(mapPath);
}

GameMap::~GameMap()
{
	delete grid;
	grid = NULL;
	delete tileset;
	tileset = NULL;
	for (int m = 0; m < this->rows; m++) {
		delete mapIDs[m];
		mapIDs[m] = NULL;
	}
	delete mapIDs;
	mapIDs = NULL;
}


void GameMap::SetMapGrid()
{
	//BoxCollider gridRect = BoxCollider(GetHeight(), 0, GetWidth(), 0);
	//grid = new Grid(gridRect, GetHeight(), GetWidth());

	//// Demo add new enemy to Grid
	//DemoEnemy* demoEnemy1 = new DemoEnemy();
	//demoEnemy1->SetPosition(500, 150);
	//new Unit(grid, demoEnemy1);

	//DemoEnemy* demoEnemy2 = new DemoEnemy();
	//demoEnemy2->SetPosition(700, 300);
	//new Unit(grid, demoEnemy2);
}

bool GameMap::isContain(BoxCollider rect1, BoxCollider rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}


int GameMap::GetWidth()
{
	return tileset->GetTileWidth() * columns;
}

int GameMap::GetHeight()
{
	return tileset->GetTileHeight() * rows;
}

int GameMap::GetTileWidth()
{
	return tileset->GetTileWidth();
}

int GameMap::GetTileHeight()
{
	return tileset->GetTileHeight();
}

void GameMap::SetCamera(Camera* cam)
{
	this->Cam = cam;
}
Grid* GameMap::GetGrid()
{
	return grid;
}

void GameMap::Draw() {

	for (size_t i = 0; i < 1; i++) {

		//chieu dai va chieu rong cua tile
		int tileWidth = tileset->GetTileWidth();
		int tileHeight = tileset->GetTileHeight();

		for (int m = 0; m < this->rows; m++) {
			for (int n = 0; n < this->columns ; n++) {
				int id = mapIDs[m][n];

				LPSPRITE sprite = tileset->GetSprite(id);
				BoxCollider spriteBound;
				spriteBound.top = (rows - m - 1) * tileHeight;
				spriteBound.bottom = spriteBound.top - tileHeight;
				spriteBound.left = n * tileWidth;
				spriteBound.right = spriteBound.left + tileWidth;

				if (Cam->IsCollide(spriteBound)) {
					D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, (rows - m - 1) * tileHeight + tileHeight / 2, 0);
					sprite->SetHeight(tileHeight);
					sprite->SetWidth(tileWidth);
					sprite->Draw(position, BoxCollider());
				}
			}

		}
	}

}
void GameMap::LoadTileset(char* filePath, int tileWidth, int tileHeight) {
	//Parse map tu file 
	Textures::GetInstance()->Add(234, filePath, D3DCOLOR_XRGB(255, 0, 255));
	auto texture = Textures::GetInstance()->GetTexture(234);
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	auto width = desc.Width;
	auto height = desc.Height;
	tileset = new Tileset(height / tileHeight, width / tileWidth, tileWidth, tileHeight);

	for (int j = 0; j < tileset->GetColumns(); j++) {
		for (int i = 0; i < tileset->GetRows(); i++) {
			BoxCollider r;
			r.top = i * tileHeight;
			r.left = j * tileWidth;
			r.bottom = r.top + tileHeight;
			r.right = r.left + tileWidth;
			LPSPRITE sprite = new Sprites(texture, r);
			tileset->Add(j * tileset->GetRows() + i, sprite);
		}
	}
}

void GameMap::SetMapPath(char* mapPath)
{
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}

	reader >> columns;
	reader >> rows;
	mapIDs = new int* [rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}

}

void GameMap::SetMapPathGridBuildIn(char* mapPath)
{
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}

	reader >> columns;
	reader >> rows;
	mapIDs = new int* [rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}
}
