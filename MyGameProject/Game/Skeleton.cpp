#include "Skeleton.h"

Skeleton::Skeleton() : Enemy() {
	SetTag(SKELETON);

	skeletonIdleState = new SkeletonIdleState(enemyData);
	point = 100;
	SetIsCollidable(false);
	Hp = 1;
	isAttack = false;
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(float dt)
{
	Enemy::Update(dt);
}

void Skeleton::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
	Enemy::OnCollision(impactor, side, collisionTime, dt);
}

void Skeleton::SetState(EnemyState::eState state)
{
	if ((state == EnemyState::Idle)) {
		enemyData->enemyState = skeletonIdleState;
		currentStateName = EnemyState::Idle;
	}
	enemyData->enemyState->ResetState();
}

void Skeleton::SetSpawnBox(BoxCollider box, int direction)
{
	Enemy::SetSpawnBox(box, direction);
	SetColliderTop(54);
	SetColliderBottom(-25);
	SetColliderRight(34);
	SetColliderLeft(-34);
}

void Skeleton::Spawn()
{
	SetState(EnemyState::Idle);
	Enemy::Spawn();

	enemyData->enemy->SetBodyBox(51, -18,34, -25);
	collider = bodyBox;
}

