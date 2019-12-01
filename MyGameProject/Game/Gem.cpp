#include "Gem.h"

Gem::Gem() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_GEM, "Resources/Items/gem.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_GEM), 1, 9, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_GEM)->GetLevelDesc(0, &desc);
	width = desc.Width / 9;
	height = desc.Height;
}

Gem::~Gem()
{
}

void Gem::Update(float dt)
{
	animation->Update(dt);
}

void Gem::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
