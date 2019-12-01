#include "Skeleton.h"

Skeleton::Skeleton()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_SKELETON, "Resources/Enemys/skeleton.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_SKELETON), BoxCollider());
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(float dt)
{
}

void Skeleton::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), spawnDirection == MoveDirection::RightToLeft);
}
