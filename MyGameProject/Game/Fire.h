#pragma once
#include "Weapon.h"

class Fire : public Weapon {
public:
	Fire();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60) override;
	void Instantiate(D3DXVECTOR3 position) override;
	void OnDestroy() override;
};