#include "GameMap.h"

GameMap::GameMap(char* filePath)
{
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	delete mMap;
}

void GameMap::LoadMap(char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();


	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset* tileset = mMap->GetTileset(i);

		Sprites* sprite = new Sprites(tileset->GetImage()->GetSource().c_str());

		mListTileset.insert(std::pair<int, Sprites*>(i, sprite));
	}
}

bool GameMap::isContain(BoxCollider rect1, BoxCollider rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}

Tmx::Map* GameMap::GetMap()
{
	return mMap;
}

int GameMap::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
	return mMap->GetTileHeight();
}

void GameMap::SetCamera(Camera* cam)
{
	camera = cam;
}
void GameMap::Draw()
{

	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		BoxCollider sourceRECT;

		int tileWidth = mMap->GetTileWidth();
		int tileHeight = mMap->GetTileHeight();

		for (size_t m = 0; m < layer->GetHeight(); m++)
		{
			for (size_t n = 0; n < layer->GetWidth(); n++)
			{
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);

				if (tilesetIndex != -1)
				{
					const Tmx::Tileset* tileSet = mMap->GetTileset(tilesetIndex);

					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

					Sprites* sprite = mListTileset[layer->GetTileTilesetIndex(n, m)];

					//tile index
					int tileID = layer->GetTileId(n, m);

					int y = tileID / tileSetWidth;
					int x = tileID - y * tileSetWidth;

					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					BoxCollider spriteBound;
					spriteBound.top = (layer->GetHeight() - m - 1) * tileHeight;
					spriteBound.bottom = spriteBound.top - tileHeight;
					spriteBound.left = n * tileWidth;
					spriteBound.right = spriteBound.left + tileWidth;

					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);

					if (mCamera->IsCollide(spriteBound)) {
						D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, (layer->GetHeight() - m - 1) * tileHeight + tileHeight / 2, 0);
						sprite->SetHeight(tileHeight);
						sprite->SetWidth(tileWidth);
						sprite->Draw(position, sourceRECT);
					}
				}
			}
		}
	}
}

void GameMap::SetCamera(Camera* camera)
{
	this->mCamera = camera;
}
