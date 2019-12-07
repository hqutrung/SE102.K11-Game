#include "ThinGuardIdleState.h"

ThinGuardIdleState::ThinGuardIdleState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 4, 2, 4, 2, 2, 8, 10, 0.04f, D3DCOLOR_XRGB(255, 0, 255));
}

void ThinGuardIdleState::Update(float dt)
{
	//....
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	enemy->SetIsCollidable(false);
}

void ThinGuardIdleState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-15);
	e->SetColliderRight(24);
	e->SetColliderTop(33);
	e->SetColliderBottom(-26);
}
