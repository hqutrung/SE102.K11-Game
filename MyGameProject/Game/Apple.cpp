#include "Apple.h"

Apple::Apple()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_APPLE, "Resources/Items/apple.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_APPLE), BoxCollider());
}

Apple::~Apple()
{
}

void Apple::Update(float dt)
{
}

void Apple::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
