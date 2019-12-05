#pragma once
#include "Enemy.h"
#include "Textures.h"

class ThinGuard : public Enemy {
public:
	ThinGuard();
	~ThinGuard();
	void Update(float dt) override;
};
