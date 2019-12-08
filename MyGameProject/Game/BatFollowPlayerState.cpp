#include "BatFollowPlayerState.h"

BatFollowPlayerState::BatFollowPlayerState(EnemyData* data) : EnemyState(data)
{
	Textures* textures = Textures::GetInstance();
	e_Animation = new Animation();
	e_Animation->AddFrames(textures->GetTexture(TEX_BAT), 1, 9, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
	auto enemy = enemyData->enemy;
}

int flag = 1;
int dir = 1;

void BatFollowPlayerState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	D3DXVECTOR2 dis = enemy->GetDisToPlayer();
	//....
	if (flag == 1) {
		if (dis.x <= 0)
			dir = -1;
		else
			dir = 1;
	}
	D3DXVECTOR3 target;

	switch (flag)
	{
	case 1:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(44 * dir, -63, 0);
		break;
	case 2:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(44 * dir, -94, 0);
		break;
	case 3:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(10 * dir, -122, 0);
		break;
	case 4:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-30 * dir, -120, 0);
		break;
	case 5:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-24 * dir, -56, 0);
		break;
	case 6:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-105 * dir, -100, 0);
		break;
	case 7:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-130 * dir, -32, 0);
		break;
	case 8:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-85 * dir, -16, 0);
		break;
	case 9:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-32 * dir, -74, 0);
		break;
		//case 10:
		//	target = GetSpawnPosition() + D3DXVECTOR3(-14, -65, 0);
		//	break;
	case 10:
		target = enemy->GetSpawnPosition();
		break;
	default:
		break;
	}

	time += dt / 0.25f;
	if (time > 1) {
		time = 1;
		flag++;
		startPos = target;
	}
	if (flag > 10) {
		flag = 1;
		enemy->SetState(EnemyState::Idle);
	}
	if (time == 1)
		time = 0;
	enemy->SetPosition(Support::Lerp(startPos.x, target.x, time), Support::Lerp(startPos.y, target.y, time));
	e_Animation->Update(dt);
	if (e_Animation->GetCurrentFrameID() == 0)
		e_Animation->SetCurrentFrame(2);
}

void BatFollowPlayerState::ResetState()
{
	auto enemy = enemyData->enemy;
	startPos = enemy->GetSpawnPosition();
}
