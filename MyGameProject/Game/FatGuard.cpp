#include "FatGuard.h"

FatGuard::FatGuard() : Enemy()
{
	SetTag(FATGUARD);
	fatguardAttackState = new FatGuardAttackState(enemyData);
	fatGuardFollowPlayerState = new FatGuardFollowPlayerState(enemyData);
	fatGuardProvokeState = new FatGuardProvokeState(enemyData);
	fatGuardIdleState = new FatGuardIdleState(enemyData);
	point = 100;
}

FatGuard::~FatGuard()
{
}

void FatGuard::Update(float dt)
{
	auto player = Player::GetInstance();
	D3DXVECTOR2 dis = GetDisToPlayer();

	//Enemy::Update(dt);
	// SetState
	if(dis.y < 5)
	{
		if (player->GetRect().bottom < GetRect().top) {

			/*if (player->GetPosition().x - spawnPosition.x > 175 || player->GetPosition().x - spawnPosition.x < -280) {
				SetState(EnemyState::Idle);
			}
			else*/
				SetState(abs(dis.x) > 120 ? EnemyState::Follow : EnemyState::Attack);
		}
		else
			SetState(EnemyState::Provoke);
		//...MoveDirection
		SetMoveDirection(dis.x < 0 ? Entity::MoveDirection::LeftToRight : Entity::MoveDirection::RightToLeft);
	}
	if (player->GetPosition().x - spawnPosition.x > 175 || player->GetPosition().x - spawnPosition.x < -280) {
		SetState(EnemyState::Idle);
	}
	Enemy::Update(dt);
}

void FatGuard::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
}

void FatGuard::SetState(EnemyState::eState state)
{
	switch (state)
	{
	case EnemyState::Idle:
		enemyData->enemyState = fatGuardIdleState;
		break;
	case EnemyState::Run:
		break;
	case EnemyState::Attack:
		enemyData->enemyState = fatguardAttackState;
		break;
	case EnemyState::Follow:
		enemyData->enemyState = fatGuardFollowPlayerState;
		break;
	case EnemyState::Provoke:
		enemyData->enemyState = fatGuardProvokeState;
		break;
	default:
		break;
	}
	enemyData->enemyState->ResetState();
}

void FatGuard::Spawn()
{
	SetState(EnemyState::Idle);
	Enemy::Spawn();
}
