#pragma once
#include "Item.h"
#include "Textures.h"

class GenieToken : public Item {
public:
	GenieToken();
	~GenieToken();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};