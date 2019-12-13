#include "ThinGuardFollowPlayer.h"

ThinGuardFollowPlayerState::ThinGuardFollowPlayerState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 4, 3, 4, 10, 10, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));
}

void ThinGuardFollowPlayerState::Update(float dt)
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

void ThinGuardFollowPlayerState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-15);
	e->SetColliderRight(24);
	e->SetColliderTop(33);
	e->SetColliderBottom(-26);
	e->SetBodyBox(32, -15, 26, -26);
}
