#pragma once
#include "Enemy.h"
#include "Sprites.h"
#include "Textures.h"

class FatGuard : public Enemy {
	Sprites* sprite;
public:
	FatGuard();
	~FatGuard();
	void Update(float dt) override;
	void Render() override;
};
