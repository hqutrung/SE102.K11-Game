#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "ThinGuardAttackState.h"
#include "ThinGuardFollowPlayer.h"
#include "ThinGuardIdleState.h"
#include "ThinGuardInjuredState.h"

class ThinGuard : public Enemy {

protected:
	EnemyState* thinGuardAttackState,
		* thinGuardFollowPlayerState,
		* thinGuardIdlePlayerState,
		* thinGuardInjuredState;
public:
	ThinGuard();
	~ThinGuard();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = 1.0f / 60) override;
	void SetState(EnemyState::eState state);
	void Spawn();
};
