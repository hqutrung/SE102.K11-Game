#include "FatGuardIdleState.h"

FatGuardIdleState::FatGuardIdleState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 1, 1, 1, 1, 1, 8, 10, 0.04f, D3DCOLOR_XRGB(255, 0, 255));
}

void FatGuardIdleState::Update(float dt)
{
	//....
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	enemy->SetIsCollidable(false);
}

void FatGuardIdleState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-17);
	e->SetColliderRight(29);
	e->SetColliderTop(22);
	e->SetColliderBottom(-26);
}
