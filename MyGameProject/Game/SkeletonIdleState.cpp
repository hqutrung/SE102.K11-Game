#include "SkeletonIdleState.h"

SkeletonIdleState::SkeletonIdleState(EnemyData* data) : EnemyState(data)
{
	isExplosive = false;
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 7, 1, 8, 10, 10, 8, 10, 0.08f, D3DCOLOR_XRGB(255, 0, 255));
}

void SkeletonIdleState::Update(float dt)
{
	auto skeleton = (Skeleton*)enemyData->enemy;
	auto disToPlayer = skeleton->GetDisToPlayer();
	if (!enemyData->enemy->isDied) {
		if(e_Animation->GetCurrentFrameID() == 19)
			e_Animation->SetDefaultTime(0.4f);
		if (e_Animation->IsLastFrame(dt))
		{
			flag = true;
			e_Animation->SetCurrentFrame(4);
			e_Animation->SetDefaultTime(0.033f);
		}
		if (flag) {
			e_Animation->Update1(dt);
			if(e_Animation->GetCurrentFrameID() == 3)
				skeleton->Explosive();
			if (e_Animation->GetCurrentFrameID() == 0)
				skeleton->isDied = true;
		}
		else
		{
			if (Support::LengthOfVector(disToPlayer) <= 155 && enemyData->enemy->IsActived())
				e_Animation->Update(dt);
			else
				e_Animation->SetCurrentFrame(0);
		}
	}
}

void SkeletonIdleState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void SkeletonIdleState::ResetState()
{
}

