#pragma once
#include "Entity.h"
#include "Animation.h"
#include "PlayerData.h"
#include "KeyBoard.h"
#include "GameConfig.h"
#include "Textures.h"

class PlayerState {
public:
	enum State {
		Idle,
		Run,
		IdleAttack,
		RunAttack,
		Duck,
		DuckAttack,
		Slide,
		LookUp,
		LookUpAttack,
		Jump,
		Fall,
		JumpCross,
		JumpAttack,
		IdleThrow,
		DuckThrow,
		RunThrow,
		JumpThrow,
		Climb,
		ClimbAttack,
		ClimbThrow,
		ClimbJump,
		Injured,
		Death,
		Push,
		TouchGroud,
		Somersault

	};
	~PlayerState();
	PlayerState();

	virtual void Update(float dt);
	virtual void Render();
	virtual void HandleInput();

	virtual BoxCollider GetBody();
	virtual State GetStateName();
	virtual void ResetState(int dummy);
	Animation* GetAnimation() { return m_Animation; }

	virtual void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60);

	bool heavy = false;
	int countPressKey = 1;
protected:
	Animation* m_Animation;
	PlayerState(PlayerData* data);
	PlayerData* playerData;
};
