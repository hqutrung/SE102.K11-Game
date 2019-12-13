#include "FatGuardProvokeState.h"

FatGuardProvokeState::FatGuardProvokeState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 3, 1, 3, 5, 5, 8, 10, 0.08f, D3DCOLOR_XRGB(255, 0, 255));
}

void FatGuardProvokeState::Update(float dt)
{
	//....
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	e_Animation->Update(dt);
}

void FatGuardProvokeState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-17);
	e->SetColliderRight(29);
	e->SetColliderTop(22);
	e->SetColliderBottom(-26);


	enemyData->enemy->SetBodyBox(22, -19, 47, -26);
}
