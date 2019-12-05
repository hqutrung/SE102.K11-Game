#include "Skeleton.h"

Skeleton::Skeleton() : Enemy() {
	SetTag(SKELETON);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_SKELETON, "Resources/Enemys/skeleton.png", D3DCOLOR_XRGB(255, 255, 255));
	
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(float dt)
{
}
