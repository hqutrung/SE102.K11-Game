#include "FatGuardInjuredState.h"

FatGuardInjuredState::FatGuardInjuredState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 3, 6, 4, 1, 10, 8, 10, 0.08f, D3DCOLOR_XRGB(255, 0, 255));
}

void FatGuardInjuredState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	if (e_Animation->IsLastFrame(dt)) {
		enemy->SetState(Idle);
	}
	e_Animation->Update(dt);
}

void FatGuardInjuredState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-17);
	e->SetColliderRight(29);
	e->SetColliderTop(22);
	e->SetColliderBottom(-26);

	enemyData->enemy->SetBodyBox(22, -19, 36, -26);
}
