#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "BatFollowPlayerState.h"
#include "BatIdleState.h"

class Bat : public Enemy {
	D3DXVECTOR3 startPos;
protected:
	EnemyState  *batFollowPlayerState,
				*batIdleState;
public:
	Bat();
	~Bat();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60);
	void SetState(EnemyState::eState state);
	void Spawn();
};
