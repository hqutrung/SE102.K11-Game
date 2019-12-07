#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "FatGuardAttackState.h"
#include "FatGuardFollowPlayerState.h"
#include "FatGuardProvokeState.h"
#include "FatGuardIdleState.h"

class FatGuard : public Enemy {

protected:
	EnemyState  *fatGuardIdleState,
				*fatguardAttackState,
			    *fatGuardFollowPlayerState,
				*fatGuardProvokeState;
public:
	FatGuard();
	~FatGuard();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60);
	void SetState(EnemyState::eState state);
	void Spawn();
};
