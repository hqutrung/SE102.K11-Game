#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class ChainedPillar : public Item {
	Sprites* sprite;
public:
	ChainedPillar();
	~ChainedPillar();
	void Update(float dt) override;
	void Render() override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};