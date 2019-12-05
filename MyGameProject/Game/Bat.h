#pragma once
#include "Enemy.h"
#include "Textures.h"

class Bat : public Enemy {
protected:
	EnemyState* batAttackState;
public:
	Bat();
	~Bat();
	void Update(float dt) override;
};
