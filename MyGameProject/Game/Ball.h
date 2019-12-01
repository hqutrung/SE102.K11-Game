#pragma once
#include "Item.h"
#include "Textures.h"
#include "Animation.h"

class Ball : public Item {
	Animation* animation;
public:
	Ball();
	~Ball();
	void Update(float dt) override;
	void Render() override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};