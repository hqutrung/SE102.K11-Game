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
		IdleThrow

	};
	~PlayerState();
	PlayerState();
	virtual void Update(float dt);
	virtual void Render();
	virtual void HandleInput();
	Animation* GetAnimation() { return m_Animation; }

//	virtual void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60);
	/*virtual State GetState();
	virtual int GetAnimationHeight();
	virtual int GetAnimationWidth();
	virtual BoxCollider GetBody();
	virtual void ResetState(int dummy);*/
protected:
	Animation* m_Animation;
	PlayerState(PlayerData* data);
	
	PlayerData* playerData;
};
