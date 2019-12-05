#include "ThinGuard.h"

ThinGuard::ThinGuard() : Enemy()
{
	SetTag(THINGUARD);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_THINGUARD, "Resources/Enemys/thinguard.png", D3DCOLOR_XRGB(255, 255, 255));

}

ThinGuard::~ThinGuard()
{
}

void ThinGuard::Update(float dt)
{
}
