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
	void SetState(EnemyState::eState state);
	void SetSpawnBox(BoxCollider box, int direction) override;
	void Spawn();
	void Explosive();
};
