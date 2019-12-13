#include "ThinGuardAttackState.h"
#include "Enemy.h"

ThinGuardAttackState::ThinGuardAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 5, 1, 5, 7, 7, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));
}

void ThinGuardAttackState::Update(float dt)
{
	//....
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	e_Animation->Update(dt);

}

void ThinGuardAttackState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-20);
	e->SetColliderRight(78);
	e->SetColliderTop(48);
	e->SetColliderBottom(-26);
	e->SetBodyBox(33, -12, 54, -26);

}
