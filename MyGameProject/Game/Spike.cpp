#include "Spike.h"

Spike::Spike() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_SPIKE, "Resources/Items/spike.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_SPIKE), BoxCollider());
}

Spike::~Spike()
{
}

void Spike::Update(float dt)
{
}

void Spike::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
