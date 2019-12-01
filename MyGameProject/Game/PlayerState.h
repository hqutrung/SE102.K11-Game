#pragma once
#include "Entity.h"
#include "Animation.h"
#include "PlayerData.h"
#include "KeyBoard.h"
#include "GameConfig.h"
#include "Textures.h"
#include "PlayerData.h"

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
		Death

	};
	int countPressKey = 1;
	~PlayerState();
	PlayerState();
	virtual void Update(float dt);
	virtual void Render();
	virtual void HandleInput();
	virtual State GetStateName();
	virtual void ResetState();
	Animation* GetAnimation() { return m_Animation; }

	virtual void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = SPF);
	/*virtual int GetAnimationHeight();
	virtual int GetAnimationWidth();
	virtual BoxCollider GetBody();*/
	virtual void ResetState(int dummy);
protected:
	Animation* m_Animation;
	PlayerState(PlayerData* data);
	
	PlayerData* playerData;
};
