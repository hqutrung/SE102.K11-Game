#include "GameMap.h"
#include "Apple.h"
#include "Gem.h"
#include "BlueHeart.h"
#include "GenieToken.h"
#include "BlueVase.h"
#include "Stone.h"
#include "Ball.h"
#include "Spike.h"
#include "Pillar.h"
#include "ExitPort.h"
#include "Bat.h"
#include "Skeleton.h"
#include "ThinGuard.h"
#include "FatGuard.h"
#include "ChainedPillar.h"

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

GameMap::GameMap(char* tilesetPath, char* mapPath, char* gridPath, int tileHeight , int tileWidth, bool gridBuilt)
{
	LoadTileset(tilesetPath, tileWidth, tileHeight);
	SetMap(mapPath, gridPath, gridBuilt);
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

int GameMap::GetRows()
{
	return rows;
}

int GameMap::GetColumns()
{
	return columns;
}

void GameMap::SetCamera(Camera* cam)
{
	this->Cam = cam;
}
Grid* GameMap::GetGrid()
{
	return grid;
}

void GameMap::LoadTileset(char* filePath, int tileWidth, int tileHeight) {
	//Parse map tu file 
	Textures::GetInstance()->Add(2911, (char*)"Resources/khung.png", D3DCOLOR_XRGB(255, 0, 255));
	Textures::GetInstance()->Add(234, filePath, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->GetTexture(234);
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

void GameMap::SetMap(char* mapPath, char* gridPath, bool gridBuilt)
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

	if (gridBuilt)
		SetGridBuilt(gridPath);
	else
		SetGrid(gridPath);
}

void GameMap::SetGrid(char* gridPath)
{
	std::fstream reader(gridPath);
	if (reader.fail()) {
		return;
	}

	BoxCollider gridRect = BoxCollider(GetHeight(), 0, GetWidth(), 0);
	//grid = new Grid(gridRect, 71, 141);
	grid = new Grid(gridRect, GRID_ROW_NUMBERS, GRID_COLUMN_NUMBERS);

	reader >> mapObjects;
	int id = 0;
	int posx = 0;
	int posy = 0;
	int wid = 0;
	int hei = 0;
	int direction = 0;

	Unit* unit;

	for (int i = 0; i < mapObjects; i++) {
		reader >> id;
		reader >> posx;
		reader >> posy;
		reader >> wid;
		reader >> hei;
		reader >> direction;

		if (id == (int)Tag::GROUND) {
			Entity* ground = new Entity();
			ground->SetTag((Tag)id);
			ground->SetType(Layer::StaticType);
			ground->SetStatic(true);
			ground->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ground->SetWidth(wid);
			ground->SetHeight(hei);
			grid->AddStaticObject(ground);
			continue;
		}

		BoxCollider box;
		box.top = posy;
		box.left = posx;
		box.bottom = posy - hei;
		box.right = posx + wid;

		switch (id)
		{
		case BAT:
		{
			Bat* bat = new Bat();
			bat->SetSpawnBox(box, direction);
			unit = new Unit(grid, bat);
			break;
		}
		case SKELETON:
		{
			Skeleton* skeleton = new Skeleton();
			skeleton->SetSpawnBox(box, direction);
			unit = new Unit(grid, skeleton);
			break;
		}
		case THINGUARD:
		{
			ThinGuard* thinGuard = new ThinGuard();
			thinGuard->SetSpawnBox(box, direction);
			unit = new Unit(grid, thinGuard);
			break;
		}
		case FATGUARD:
		{
			FatGuard* fatGuard = new FatGuard();
			fatGuard->SetSpawnBox(box, direction);
			unit = new Unit(grid, fatGuard);
			break;
		}
		case PEDDLER:
		{
			break;
		}
		case CARPET:
		{
			break;
		}
		case JAFAR:
		{
			break;
		}
		case APPLE:
		{
			Apple* apple = new Apple();
			apple->SetSpawnBox(box);
			unit = new Unit(grid, apple);
			break;
		}
		case BLUEHEART:
		{
			BlueHeart* blueheart = new BlueHeart();
			blueheart->SetSpawnBox(box);
			unit = new Unit(grid, blueheart);
			break;
		}
		case GEM:
		{
			Gem* gem = new Gem();
			gem->SetSpawnBox(box);
			unit = new Unit(grid, gem);
			break;
		}
		case GENIETOKEN:
		{
			GenieToken* genieToken = new GenieToken();
			genieToken->SetSpawnBox(box);
			unit = new Unit(grid, genieToken);
			break;
		}
		case BLUEVASE:
		{
			BlueVase* blueVase = new BlueVase();
			blueVase->SetSpawnBox(box);
			unit = new Unit(grid, blueVase);
			break;
		}
		case STONE:
		{
			Stone* stone = new Stone();
			stone->SetSpawnBox(box);
			unit = new Unit(grid, stone);
			break;
		}
		case BALL:
		{
			Ball* ball = new Ball();
			ball->SetSpawnBox(box);
			unit = new Unit(grid, ball);
			break;
		}
		case SPIKE:
		{
			Spike* spike = new Spike();
			spike->SetSpawnBox(box);
			unit = new Unit(grid, spike);
			break;
		}
		case EXITPORT:
		{
			ExitPort* exitPort = new ExitPort();
			exitPort->SetSpawnBox(box);
			unit = new Unit(grid, exitPort);
			break;
		}
		case CHAINEDPILLAR:
		{
			/*ChainedPillar* chainedPillar = new ChainedPillar();
			chainedPillar->SetSpawnBox(box);
			unit = new Unit(grid, chainedPillar);*/
			break;
		}
		default:
			break;
		}
	}
}

void GameMap::SetGridBuilt(char* gridBuiltPath)
{
	std::fstream reader(gridBuiltPath);
	if (reader.fail()) {
		return;
	}

	int gridRows, gridColumns;

	reader >> gridRows;
	reader >> gridColumns;
	
	BoxCollider gridRect = BoxCollider(GetHeight(), 0, GetWidth(), 0);
	grid = new Grid(gridRect, gridRows, gridColumns);

	reader >> mapObjects;

	int id = 0;
	int posx = 0;
	int posy = 0;
	int wid = 0;
	int hei = 0;
	int direction = 0;
	int cellX = 0;
	int cellY = 0;


	Unit* unit;

	for (int i = 0; i < mapObjects; i++) {
		reader >> id;
		reader >> posx;
		reader >> posy;
		reader >> wid;
		reader >> hei;
		reader >> direction;
		reader >> cellX;
		reader >> cellY;

		if (id == (int)Tag::GROUND || id == (int)Tag::WALL || id == (int)Tag::CHAINE) {
			Entity* ent = new Entity();
			ent->SetTag((Tag)id);
			ent->SetType(Layer::StaticType);
			ent->SetStatic(true);
			ent->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ent->SetWidth(wid);
			ent->SetHeight(hei);
			grid->AddStaticObject(ent);
			continue;
		}

		BoxCollider box;
		box.top = posy;
		box.left = posx;
		box.bottom = posy - hei;
		box.right = posx + wid;

		switch (id)
		{
		case BAT:
		{
			Bat* bat = new Bat();
			bat->SetSpawnBox(box, direction);
			unit = new Unit(grid, bat);
			break;
		}
		case SKELETON:
		{
			Skeleton* skeleton = new Skeleton();
			skeleton->SetSpawnBox(box, direction);
			unit = new Unit(grid, skeleton);
			break;
		}
		case THINGUARD:
		{
			ThinGuard* thinGuard = new ThinGuard();
			thinGuard->SetSpawnBox(box, direction);
			unit = new Unit(grid, thinGuard);
			break;
		}
		case FATGUARD:
		{
			FatGuard* fatGuard = new FatGuard();
			fatGuard->SetSpawnBox(box, direction);
			unit = new Unit(grid, fatGuard);
			break;
		}
		case PEDDLER:
		{
			break;
		}
		case CARPET:
		{
			break;
		}
		case JAFAR:
		{
			break;
		}
		case APPLE:
		{
			Apple* apple = new Apple();
			apple->SetSpawnBox(box);
			unit = new Unit(grid, apple);
			break;
		}
		case BLUEHEART:
		{
			BlueHeart* blueheart = new BlueHeart();
			blueheart->SetSpawnBox(box);
			unit = new Unit(grid, blueheart);
			break;
		}
		case GEM:
		{
			Gem* gem = new Gem();
			gem->SetSpawnBox(box);
			unit = new Unit(grid, gem);
			break;
		}
		case GENIETOKEN:
		{
			GenieToken* genieToken = new GenieToken();
			genieToken->SetSpawnBox(box);
			unit = new Unit(grid, genieToken);
			break;
		}
		case BLUEVASE:
		{
			BlueVase* blueVase = new BlueVase();
			blueVase->SetSpawnBox(box);
			unit = new Unit(grid, blueVase);
			break;
		}
		case STONE:
		{
			Stone* stone = new Stone();
			stone->SetSpawnBox(box);
			unit = new Unit(grid, stone);
			break;
		}
		case BALL:
		{
			Ball* ball = new Ball();
			ball->SetSpawnBox(box);
			unit = new Unit(grid, ball);
			break;
		}
		case SPIKE:
		{
			Spike* spike = new Spike();
			spike->SetSpawnBox(box);
			unit = new Unit(grid, spike);
			break;
		}
		case EXITPORT:
		{
			ExitPort* exitPort = new ExitPort();
			exitPort->SetSpawnBox(box);
			grid->AddStaticObject(exitPort);
			break;
		}
		case CHAINEDPILLAR:
		{
			ChainedPillar* chainedPillar = new ChainedPillar();
			chainedPillar->SetSpawnBox(box);
			grid->AddStaticObject(chainedPillar);
			break;
		}
		case PILLAR1:
		{
			Pillar* pillar = new Pillar(1);
			pillar->SetSpawnBox(box);
			grid->AddStaticObject(pillar);
			break;
		}
		case PILLAR2:
		{
			Pillar* pillar = new Pillar(2);
			pillar->SetSpawnBox(box);
			grid->AddStaticObject(pillar);
			break;
		}
		case PILLAR3:
		{
			Pillar* pillar = new Pillar(3);
			pillar->SetSpawnBox(box);
			grid->AddStaticObject(pillar);
			break;
		}
		case PILLAR4:
		{
			Pillar* pillar = new Pillar(4);
			pillar->SetSpawnBox(box);
			grid->AddStaticObject(pillar);
			break;
		}
		default:
			break;
		}
	}
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

				BoxCollider spriteBound;
				spriteBound.top = (rows - m) * tileHeight;
				spriteBound.bottom = spriteBound.top - tileHeight;
				spriteBound.left = n * tileWidth;
				spriteBound.right = spriteBound.left + tileWidth;

				if (!Cam->IsCollide(spriteBound)) {
					continue;
				}
				D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, (rows - m - 1) * tileHeight + tileHeight / 2, 0);
				sprite->SetHeight(tileHeight);
				sprite->SetWidth(tileWidth);
				sprite->Draw(position, BoxCollider());
			}

		}
	}
}