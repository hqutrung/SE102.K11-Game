#pragma once
#include "Enemy.h"
#include "Sprites.h"
#include "Textures.h"
#include "Player.h"

class FatGuard : public Enemy {
	Sprites* sprite;
public:
	FatGuard();
	~FatGuard();
	void Update(float dt) override;
	bool followPlayer(D3DXVECTOR3 dispos) override;
};
