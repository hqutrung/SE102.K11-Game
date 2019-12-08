#include "FatGuardFollowPlayerState.h"

FatGuardFollowPlayerState::FatGuardFollowPlayerState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 2, 2, 2, 10, 10, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));
}

void FatGuardFollowPlayerState::Update(float dt)
{

	auto enemy = enemyData->enemy;
	D3DXVECTOR2 dis = enemy->GetDisToPlayer();
	if (dis.x < 0) {
		enemy->SetVx(FATGUARD_RUNSPEED);
	}
	else {
		enemy->SetVx(-FATGUARD_RUNSPEED);
	}
	e_Animation->Update(dt);

}

void FatGuardFollowPlayerState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-17);
	e->SetColliderRight(29);
	e->SetColliderTop(22);
	e->SetColliderBottom(-26);
}
