#include "BatFollowPlayerState.h"

BatFollowPlayerState::BatFollowPlayerState(EnemyData* data) : EnemyState(data)
{
	Textures* textures = Textures::GetInstance();
	e_Animation = new Animation();
	e_Animation->AddFramesA(textures->GetTexture(TEX_BAT), 1, 5, 1, 11, 11, 1, 11, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	auto enemy = enemyData->enemy;

	flag = 1;
	direction = 1;
}


void BatFollowPlayerState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	D3DXVECTOR2 dis = enemy->GetDisToPlayer();
	//....
	if (flag == 1) {
		direction = dis.x <= 0 ? -1 : 1;
	}
	D3DXVECTOR3 target;

	switch (flag)
	{
	case 1:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(22 * direction, -31, 0);
		break;
	case 2:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(44 * direction, -63, 0);
		break;
	case 3:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(44 * direction, -94, 0);
		break;
	case 4:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(10 * direction, -122, 0);
		break;
	case 5:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-30 * direction, -120, 0);
		break;
	case 6:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-24 * direction, -56, 0);
		break;
	case 7:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-65 * direction, -78, 0);
		break;
	case 8:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-105 * direction, -100, 0);
		break;
	case 9:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-130 * direction, -32, 0);
		break;
	case 10:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-85 * direction, -16, 0);
		break;
	case 11:
		target = enemy->GetSpawnPosition() + D3DXVECTOR3(-32 * direction, -74, 0);
		break;
	case 12:
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
	if (flag > 12) {
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
