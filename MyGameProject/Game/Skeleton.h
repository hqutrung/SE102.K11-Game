#pragma once
#include "Enemy.h"
#include "Textures.h"

class Skeleton : public Enemy {
public:
	Skeleton();
	~Skeleton();
	void Update(float dt) override;
};
