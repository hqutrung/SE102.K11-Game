#include "FatGuardAttackState.h"
#include "Enemy.h"

FatGuardAttackState::FatGuardAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 1, 2, 2, 1, 10, 8, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));

}

#include<random>

void FatGuardAttackState::Update(float dt)
{

	//....
	auto e = enemyData->enemy;
	e->SetVx(0);
	e->SetVy(0);

	int frameID = e_Animation->GetCurrentFrameID();


	if (e_Animation->IsLastFrame(dt))
	{
		if (e_Animation->countLoopFrame % 3 == 0)
		{
			e_Animation->SetCurrentFrame(4);
		}
		e_Animation->countLoopFrame++;
	}


	if (e_Animation->GetCurrentFrameID() >= 5)
	{

		e->SetColliderLeft(-28);
		e->SetColliderRight(75);
		e->SetColliderTop(26);
	}
	else {
		e->SetColliderLeft(-16);
		e->SetColliderRight(60);
		e->SetColliderTop(20);
	}
	enemyData->enemy->isAttack = false;
	e_Animation->Update(dt);
	switch (frameID)
	{
	case 0:
		//delay time
		if (e_Animation->countLoopFrame == 1)
			e_Animation->SetDefaultTime(0.2f);
		break;
	case 1:
	case 2:
	case 3:
		e_Animation->SetDefaultTime(0.1);
		break;
	case 4:
	case 8:
	case 9:
		enemyData->enemy->isAttack = true;
		break;
	default:
		e_Animation->SetDefaultTime(0.08);
		break;
	}
	if (e_Animation->IsLastFrame(dt))
		e_Animation->countLoopFrame++;
	
}


void FatGuardAttackState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-28);
	e->SetColliderRight(80);
	e->SetColliderTop(26);
	e->SetColliderBottom(-26);
	e_Animation->ResetAnimation();
	enemyData->enemy->SetBodyBox(19, -19, 47, -26);
}
