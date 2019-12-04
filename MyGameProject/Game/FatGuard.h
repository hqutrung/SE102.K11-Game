#pragma once
#include "Enemy.h"
#include "Sprites.h"
#include "Textures.h"
#include"EnemyData.h"
#include"EnemyState.h"

class FatGuard : public Enemy {

protected:
	EnemyState* fatguardAttackState;

public:
	FatGuard();
	~FatGuard();
	void Update(float dt) override;
	void Render() override;
};
