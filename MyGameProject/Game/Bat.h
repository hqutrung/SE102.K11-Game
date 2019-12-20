#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "BatFollowPlayerState.h"
#include "BatIdleState.h"
#include "BatRotateState.h"

class Bat : public Enemy {
	D3DXVECTOR3 startPos;
protected:
	EnemyState* batFollowPlayerState,
		* batIdleState,
		* batRotateState;
public:
	Bat();
	~Bat();
	void Update(float dt) override;
	void SetState(EnemyState::eState state);
	void Spawn();

};
