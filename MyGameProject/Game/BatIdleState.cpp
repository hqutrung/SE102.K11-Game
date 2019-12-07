#include "BatIdleState.h"

BatIdleState::BatIdleState(EnemyData* data) : EnemyState(data)
{
	Textures* textures = Textures::GetInstance();
	e_Animation = new Animation();
	e_Animation->AddFramesA(textures->GetTexture(TEX_BAT), 1, 1, 1, 1, 1, 1, 9, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
	delayTime = 1.0f;
	/*e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 1, 1, 2, 1, 10, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));*/
}

void BatIdleState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	if (delayTime < 0)
	{
		if(enemy->IsActived())
			enemy->SetState(EnemyState::Follow);
		return;
	}
	delayTime -= dt;
}

void BatIdleState::ResetState()
{
	delayTime = 1.0f;
}
