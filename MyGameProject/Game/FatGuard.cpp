#include "FatGuard.h"
#include"FatGuardAttackState.h"

FatGuard::FatGuard()
{
	Enemy();
	SetTag(FATGUARD);
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_FATGUARD, "Resources/Enemys/fatguard.png", D3DCOLOR_XRGB(255, 255, 255));

	fatguardAttackState = new FatGuardAttackState(enemyData);
	
}

FatGuard::~FatGuard()
{
}

void FatGuard::Update(float dt)
{
	
}

void FatGuard::Render()
{
	
}
