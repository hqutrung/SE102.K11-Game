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
	void SetState(EnemyState::eState state);
	void Spawn();
	void SetSpawnBox(BoxCollider box, int direction);
};
