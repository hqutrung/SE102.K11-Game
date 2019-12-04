#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "FatGuardAttackState.h"

class FatGuard : public Enemy {

protected:
	EnemyState* fatguardAttackState;
public:
	FatGuard();
	~FatGuard();
	void Update(float dt) override;
};
