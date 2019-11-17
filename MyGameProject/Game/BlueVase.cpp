#include "BlueVase.h"

BlueVase::BlueVase() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BLUEVASE, "Resources/Items/bluevase.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_BLUEVASE), BoxCollider());
}

BlueVase::~BlueVase()
{
}

void BlueVase::Update(float dt)
{
}

void BlueVase::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
