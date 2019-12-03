#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class Spike : public Obstacles {
public:
	Spike();
	~Spike();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};