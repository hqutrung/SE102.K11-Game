#include "Bat.h"

Bat::Bat()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BAT, "Resources/Enemys/bat.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_BAT), BoxCollider());
}

Bat::~Bat()
{
}

void Bat::Update(float dt)
{
}

void Bat::Render()
{
 	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
