#include "ThinGuard.h"

ThinGuard::ThinGuard() : Enemy()
{
	SetTag(THINGUARD);
	thinGuardAttackState = new ThinGuardAttackState(enemyData);
	thinGuardFollowPlayerState = new ThinGuardFollowPlayerState(enemyData);
	thinGuardIdlePlayerState = new ThinGuardIdleState(enemyData);
	thinGuardInjuredState = new ThinGuardInjuredState(enemyData);
	point = 100;
	Hp = 3;
}

ThinGuard::~ThinGuard()
{
}

void ThinGuard::Update(float dt)
{
	auto player = Player::GetInstance();
	D3DXVECTOR2 dis = GetDisToPlayer();

	//Enemy::Update(dt);
	// SetState
	if (!isInjured) {
		if (abs(dis.y) < 200)
		{
			if ((player->GetPosition().x - spawnPosition.x) > 160 || (player->GetPosition().x - spawnPosition.x) < -118) {
				SetState(EnemyState::Idle);
			}
			else
			{
				if (abs(dis.x) > 100)
					SetState(EnemyState::Follow);
				else if (abs(dis.x) > 70)
					SetState(EnemyState::Idle);
				else
					SetState(EnemyState::Attack);
				//SetState(abs(dis.x) > 100 ? EnemyState::Follow : EnemyState::Idle);
			}

			SetMoveDirection(dis.x < 0 ? Entity::MoveDirection::LeftToRight : Entity::MoveDirection::RightToLeft);
		}
	}
	Enemy::Update(dt);
}

void ThinGuard::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
	Enemy::OnCollision(impactor, side, collisionTime, dt);
}

void ThinGuard::SetState(EnemyState::eState state)
{
	isInjured = false;
	isAttack = false;
	switch (state)
	{
	case EnemyState::Idle:
		currentStateName = EnemyState::Idle;
		enemyData->enemyState = thinGuardIdlePlayerState;
		break;
	case EnemyState::Attack:
		currentStateName = EnemyState::Attack;
		enemyData->enemyState = thinGuardAttackState;
		isAttack = true;
		break;
	case EnemyState::Follow:
		currentStateName = EnemyState::Follow;
		enemyData->enemyState = thinGuardFollowPlayerState;
		break;
	case EnemyState::Injured:
		currentStateName = EnemyState::Injured;
		enemyData->enemyState = thinGuardInjuredState;
		isInjured = true;
		break;
	default:
		break;
	}
	enemyData->enemyState->ResetState();
}

void ThinGuard::Spawn()
{
	SetState(EnemyState::Idle);
	Enemy::Spawn();
}
