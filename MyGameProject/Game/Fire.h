#pragma once
#include "Weapon.h"

class Fire : public Weapon {
public:
	Fire();
	void Update(float dt) override;
	void Instantiate(D3DXVECTOR3 position) override;
	void OnDestroy() override;
};