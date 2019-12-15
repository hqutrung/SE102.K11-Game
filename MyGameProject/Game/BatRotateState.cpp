#include "BatRotateState.h"

BatRotateState::BatRotateState(EnemyData* data) : EnemyState(data)
{
	Textures* textures = Textures::GetInstance();
	e_Animation = new Animation();
	e_Animation->AddFramesA(textures->GetTexture(TEX_BAT), 1, 2, 1, 4, 4, 1, 11, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	/*e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 1, 1, 2, 1, 10, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));*/
}

void BatRotateState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	auto disToPlayer = enemy->GetDisToPlayer();
	enemy->SetVx(0);
	enemy->SetVy(0);
	if (e_Animation->IsLastFrame(dt))
		enemy->SetState(EnemyState::Follow);
	e_Animation->Update(dt);
}

void BatRotateState::ResetState()
{
}
