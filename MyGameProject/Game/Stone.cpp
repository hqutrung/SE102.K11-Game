#include "Stone.h"

Stone::Stone() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_STONE, "Resources/Items/stone.png", D3DCOLOR_XRGB(255, 255, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_STONE), 1, 8, 0.25f, D3DCOLOR_XRGB(255, 255, 255));

	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_STONE)->GetLevelDesc(0, &desc);
	width = desc.Width / 8;
	height = desc.Height;
}

Stone::~Stone()
{
}

void Stone::Update(float dt)
{
	if (animation->GetCurrentFrameID() == 0 || animation->GetCurrentFrameID() == 4)
		animation->SetDefaultTime(1.2f);
	else
		animation->SetDefaultTime(0.25f);
	animation->Update(dt);
}

void Stone::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
