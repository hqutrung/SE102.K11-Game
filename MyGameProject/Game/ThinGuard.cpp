#include "ThinGuard.h"

ThinGuard::ThinGuard()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_THINGUARD, "Resources/Enemys/thinguard.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_THINGUARD), BoxCollider());
}

ThinGuard::~ThinGuard()
{
}

void ThinGuard::Update(float dt)
{
}

void ThinGuard::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), spawnDirection == MoveDirection::LeftToRight);
}
