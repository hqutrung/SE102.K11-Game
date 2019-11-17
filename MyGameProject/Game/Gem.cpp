#include "Gem.h"

Gem::Gem() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_GEM, "Resources/Items/gem.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_GEM), BoxCollider());
}

Gem::~Gem()
{
}

void Gem::Update(float dt)
{
}

void Gem::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
