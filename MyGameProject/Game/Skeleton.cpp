#include "Skeleton.h"

Skeleton::Skeleton() : Enemy() {
	SetTag(SKELETON);

	skeletonIdleState = new SkeletonIdleState(enemyData);
	point = 100;
	
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(float dt)
{
	Enemy::Update(dt);
}

void Skeleton::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
}

void Skeleton::SetState(EnemyState::eState state)
{
	if ((state == EnemyState::Idle))
		enemyData->enemyState = skeletonIdleState;
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
}
