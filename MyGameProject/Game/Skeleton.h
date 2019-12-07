#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "SkeletonIdleState.h"

class Skeleton : public Enemy {

protected:
	EnemyState* skeletonIdleState;
public:
	Skeleton();
	~Skeleton();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60);
	void SetState(EnemyState::eState state);
	void SetSpawnBox(BoxCollider box, int direction) override;
	void Spawn();
};
