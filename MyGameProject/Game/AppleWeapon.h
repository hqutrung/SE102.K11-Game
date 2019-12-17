#pragma once
#include "Weapon.h"
#include "AppleWeaponExplosion.h"

class AppleWeapon : public Weapon {
	D3DXVECTOR2 accelery;
public:
	AppleWeapon();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60) override;
	void Instantiate(D3DXVECTOR3 position) override;
	void OnDestroy() override;
};