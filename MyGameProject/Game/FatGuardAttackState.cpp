#include "FatGuardAttackState.h"
#include "Enemy.h"

FatGuardAttackState::FatGuardAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 1, 2, 2, 1, 10, 8, 10, 0.07f, D3DCOLOR_XRGB(255, 0, 255));

}

#include<random>

void FatGuardAttackState::Update(float dt)
{
	//....
	auto e = enemyData->enemy;
	e->SetVx(0);
	e->SetVy(0);
	int frameID = e_Animation->GetCurrentFrameID();
	int rd = rand() % 3 + 3;

	if (e_Animation->IsLastFrame(dt))
	{
		if (e_Animation->countLoopFrame % rd != 0)
		{
			e_Animation->SetCurrentFrame(4);
		}
		e_Animation->countLoopFrame++;
	}


	if (e_Animation->GetCurrentFrameID() >= 5)
	{

		e->SetColliderLeft(-28);
		e->SetColliderRight(80);
		e->SetColliderTop(26);
	}
	else {
		e->SetColliderLeft(-16);
		e->SetColliderRight(43);
		e->SetColliderTop(20);
	}
	e_Animation->Update(dt);
}


void FatGuardAttackState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-28);
	e->SetColliderRight(80);
	e->SetColliderTop(26);
	e->SetColliderBottom(-26);
}
