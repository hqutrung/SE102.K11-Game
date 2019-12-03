#include "FatGuard.h"

FatGuard::FatGuard()
{
	Enemy();
	SetTag(FATGUARD);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_FATGUARD, "Resources/Enemys/fatguard.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_FATGUARD), BoxCollider());
}

FatGuard::~FatGuard()
{
}

void FatGuard::Update(float dt)
{
}

void FatGuard::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), spawnDirection == MoveDirection::LeftToRight);
}
