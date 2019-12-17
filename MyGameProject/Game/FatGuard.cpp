#include "FatGuard.h"

FatGuard::FatGuard() : Enemy()
{
	SetTag(FATGUARD);
	fatguardAttackState = new FatGuardAttackState(enemyData);
	fatGuardFollowPlayerState = new FatGuardFollowPlayerState(enemyData);
	fatGuardProvokeState = new FatGuardProvokeState(enemyData);
	fatGuardIdleState = new FatGuardIdleState(enemyData);
	fatGuardInjuredState = new FatGuardInjuredState(enemyData);
	point = 0;
	Hp = 2;
	isAttack = false;
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
			if (player->GetRect().bottom < GetRect().bottom + 10) {

				if (player->GetPosition().x - spawnPosition.x > 175 || player->GetPosition().x - spawnPosition.x < -275) {
					SetState(EnemyState::Idle);
				}
				else {
					SetState(abs(dis.x) > 120 ? EnemyState::Follow : EnemyState::Attack);
				}
			}
			else {
				SetState(EnemyState::Provoke);
			}//...MoveDirection
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
}

void FatGuard::SetState(EnemyState::eState state)
{
	if (currentStateName == state)
		return;
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
		if (!Player::GetInstance()->isReviving)
			Sound::GetInstance()->PlayFX(COME_ON);
		break;
	case EnemyState::Injured:
		currentStateName = EnemyState::Injured;
		enemyData->enemyState = fatGuardInjuredState;
		if(!isDied)
			Sound::GetInstance()->PlayFX(GUARD_INJURED);
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

void FatGuard::SetSpawnBox(BoxCollider box, int direction)
{
	Enemy::SetSpawnBox(box, direction);

	SetBodyBox(22, -19, 36, -26);

}

