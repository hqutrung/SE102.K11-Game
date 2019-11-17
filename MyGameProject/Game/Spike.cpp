#include "Spike.h"

Spike::Spike() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_SPIKE, "Resources/Items/spike.png", D3DCOLOR_XRGB(255, 255, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_SPIKE), 1, 6, 0.2f, D3DCOLOR_XRGB(255, 255, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_SPIKE)->GetLevelDesc(0, &desc);
	width = desc.Width / 6;
	height = desc.Height;
}

Spike::~Spike()
{
}

void Spike::Update(float dt)
{
	animation->Update(dt);
}

void Spike::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
