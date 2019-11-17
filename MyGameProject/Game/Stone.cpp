#include "Stone.h"

Stone::Stone() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_STONE, "Resources/Items/stone.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_STONE), BoxCollider());
}

Stone::~Stone()
{
}

void Stone::Update(float dt)
{
}

void Stone::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
