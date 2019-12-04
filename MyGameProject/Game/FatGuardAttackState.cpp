#include "FatGuardAttackState.h"
#include "Enemy.h"

FatGuardAttackState::FatGuardAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_FATGUARD), 3, 1,3,5,5,4,8, 0.08, D3DCOLOR_XRGB(255, 0, 255));

}

void FatGuardAttackState::Update(float dt)
{
	//....
	EnemyState::Update(dt);
}


void FatGuardAttackState::ResetState()
{
}
