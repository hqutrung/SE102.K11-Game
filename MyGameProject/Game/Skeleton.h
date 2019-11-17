#pragma once
#include "Enemy.h"
#include "Sprites.h"
#include "Textures.h"

class Skeleton : public Enemy {
	Sprites* sprite;
public:
	Skeleton();
	~Skeleton();
	void Update(float dt) override;
	void Render() override;
};
