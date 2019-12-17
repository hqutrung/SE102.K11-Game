#include "Gem.h"

Gem::Gem() : Item()
{
	SetTag(GEM);
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_GEM, "Resources/Items/gem.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_GEM), 1, 9, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

Gem::~Gem()
{
}

void Gem::OnDestroy()
{
	Item::OnDestroy();
	Sound::GetInstance()->PlayFX(GEM_COLLECT);
	Player::GetInstance()->AddGems();
}
