#pragma once
#include "Item.h"
#include "Textures.h"

class BlueHeart : public Item {
public:
	BlueHeart();
	~BlueHeart();
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};