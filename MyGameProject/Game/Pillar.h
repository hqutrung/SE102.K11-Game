#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Pillar : public Item {
	Sprites* sprite;
public:
	Pillar();
	~Pillar();
	void Update(float dt) override;
	void Render() override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};