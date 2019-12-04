#pragma once
#include "Item.h"
#include "Textures.h"

class Gem : public Item {
public:
	Gem();
	~Gem();
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};