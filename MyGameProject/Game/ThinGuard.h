#pragma once
#include "Enemy.h"
#include "Sprites.h"
#include "Textures.h"

class ThinGuard : public Enemy {
	Sprites* sprite;
public:
	ThinGuard();
	~ThinGuard();
	void Update(float dt) override;
	void Render() override;
};
