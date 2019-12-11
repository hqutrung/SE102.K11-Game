#include "FatGuard.h"

FatGuard::FatGuard() : Enemy()
{
	SetTag(FATGUARD);
	fatguardAttackState = new FatGuardAttackState(enemyData);
	fatGuardFollowPlayerState = new FatGuardFollowPlayerState(enemyData);
	fatGuardProvokeState = new FatGuardProvokeState(enemyData);
	fatGuardIdleState = new FatGuardIdleState(enemyData);
	fatGuardInjuredState = new FatGuardInjuredState(enemyData);
	point = 100;
	Hp = 2;
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
	if (!isInjured) {
		if (dis.y < 10)
		{
			if (player->GetRect().bottom < GetRect().top) {

				if (player->GetPosition().x - spawnPosition.x > 175 || player->GetPosition().x - spawnPosition.x < -275) {
					SetState(EnemyState::Idle);
				}
				else
					SetState(abs(dis.x) > 120 ? EnemyState::Follow : EnemyState::Attack);
			}
			else
				SetState(EnemyState::Provoke);
			//...MoveDirection
			SetMoveDirection(dis.x < 0 ? Entity::MoveDirection::LeftToRight : Entity::MoveDirection::RightToLeft);
		}
		else {
			SetState(EnemyState::Idle);
		}
	}
	Enemy::Update(dt);
}

void FatGuard::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
	Enemy::OnCollision(impactor, side, collisionTime, dt);
	/*if (impactor->GetType() == PlayerType)
	{
		auto player = (Player*)impactor;
		if (player->isAttack)
			SetState(EnemyState::Injured);
	}*/
}

void FatGuard::SetState(EnemyState::eState state)
{
	isInjured = false;
	isAttack = false;
	switch (state)
	{
	case EnemyState::Idle:
		enemyData->enemyState = fatGuardIdleState;
		currentStateName = EnemyState::Idle;
		break;
	case EnemyState::Run:
		currentStateName = EnemyState::Run;
		break;
	case EnemyState::Attack:
		currentStateName = EnemyState::Attack;
		enemyData->enemyState = fatguardAttackState;
		isAttack = true;
		break;
	case EnemyState::Follow:
		currentStateName = EnemyState::Follow;
		enemyData->enemyState = fatGuardFollowPlayerState;
		break;
	case EnemyState::Provoke:
		currentStateName = EnemyState::Provoke;
		enemyData->enemyState = fatGuardProvokeState;
		break;
	case EnemyState::Injured:
		currentStateName = EnemyState::Injured;
		enemyData->enemyState = fatGuardInjuredState;
		isInjured = true;
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
