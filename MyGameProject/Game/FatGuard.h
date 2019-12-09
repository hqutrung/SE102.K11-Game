#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "FatGuardAttackState.h"
#include "FatGuardFollowPlayerState.h"
#include "FatGuardProvokeState.h"
#include "FatGuardIdleState.h"
#include "FatGuardInjuredState.h"

class FatGuard : public Enemy {

protected:
	EnemyState* fatGuardIdleState,
		* fatguardAttackState,
		* fatGuardFollowPlayerState,
		* fatGuardProvokeState,
		* fatGuardInjuredState;
public:
	FatGuard();
	~FatGuard();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = 1.0f / 60) override;
	void SetState(EnemyState::eState state);
	void Spawn();
};
