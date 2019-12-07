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
}
