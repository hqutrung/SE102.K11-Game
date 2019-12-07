#include "SkeletonIdleState.h"

SkeletonIdleState::SkeletonIdleState(EnemyData* data) : EnemyState(data)
{
	isExplosive = false;
	delayTime = 2.0f;
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 7, 1, 8, 10, 10, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));
}

void SkeletonIdleState::Update(float dt)
{
	if (delayTime <= 0) {
		if (e_Animation->GetCurrentFrameID() == 19)
		{
			isExplosive = true;
			e_Animation->SetCurrentFrame(6);
			e_Animation->SetDefaultTime(0.04);
		}
		if (isExplosive) {
			if (e_Animation->GetCurrentFrameID() == 0)
				return;
			e_Animation->Update1(dt);
		}
		else
			e_Animation->Update(dt);
		return;
	}
	delayTime -= dt;
}

void SkeletonIdleState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void SkeletonIdleState::ResetState()
{
}
