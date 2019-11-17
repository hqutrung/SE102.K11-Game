#include "BlueHeart.h"

BlueHeart::BlueHeart() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_HEART, "Resources/Items/blueheart.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_HEART), BoxCollider());
}

BlueHeart::~BlueHeart()
{
}

void BlueHeart::Update(float dt)
{
}

void BlueHeart::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
