#include "JafarAttackState.h"

JafarAttackState::JafarAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_JAFAR), 1, 2, 1, 8, 8, 2, 10, 0.04f, D3DCOLOR_XRGB(255, 0, 255));
}

void JafarAttackState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
}

void JafarAttackState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-15);
	e->SetColliderRight(24);
	e->SetColliderTop(33);
	e->SetColliderBottom(-26);
	e->SetBodyBox(32, -15, 26, -26);
}

void JafarAttackState::UseWeapon()
{
}
