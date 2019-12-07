#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "ThinGuardAttackState.h"
#include "ThinGuardFollowPlayer.h"
#include "ThinGuardIdleState.h"

class ThinGuard : public Enemy {

protected:
	EnemyState	* thinGuardAttackState,
				* thinGuardFollowPlayerState,
				* thinGuardIdlePlayerState;
public:
	ThinGuard();
	~ThinGuard();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60);
	void SetState(EnemyState::eState state);
	void Spawn();
};
