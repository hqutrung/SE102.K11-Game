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
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = 1.0f / 60) override;
	void SetState(EnemyState::eState state);
	void SetSpawnBox(BoxCollider box, int direction) override;
	void Spawn();
	void Explosive();
};
