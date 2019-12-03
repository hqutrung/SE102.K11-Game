﻿#pragma once
#include "Entity.h"
#include "Textures.h"
#include "PlayerData.h"
#include "PlayerState.h"

class Player : public Entity {
public:
	enum Status {
		Jumping,
		Falling,
		OnGround,
		Climbing
	};

	static Player* GetInstance();
	Player();
	~Player();
	void Update(float dt) override;
	void Render() override;
	void SetState(PlayerState::State state, int dummy = 0);

	void HandleInput();

	PlayerState* GetCurrentState();
	PlayerState* GetState(PlayerState::State state);

	PlayerState::State GetPrevStateName() { return prevStateName; }
	// sử dụng cho State Jump
	Status status;
	D3DXVECTOR3 lastposition;
	//
	bool isClaimWall = false;
	//

	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);

	BoxCollider GetRect();
	BoxCollider GetBody();
	float GetBigWidth() override;
	float GetBigHeight() override;
	BoxCollider GetBigBound();
	float GetWidth() override;
	float GetHeight() override;

	void SetActive(bool active);
	void OnFalling();

	void SetMoveDirection(Entity::MoveDirection dir) override;

	//void OnImmortal();
	//void OffImmortal();

	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60) override;
	

	
	//bool checkGroundInFrame;
	//float timeOnAir;

	////bool renderPreviousFrame;
	



protected:
	static Player* instance;
	PlayerData* playerData;
	PlayerState
		* idleState,
		* runState,
		* idleAttackState,
		* runAttackState,
		* duckState,
		* duckAttackState,
		* slideState,
		* lookUpState,
		* lookUpAttackState,
		* jumpState,
		* fallState,
		* jumpCrossState,
		* jumpAttackState,
		* idleThrowState,
		* duckThrowState,
		* runThrowState,
		* jumpThrowState,
		* climbState,
		* climbAttackState,
		* climbThrowState,
		* climbJumpState,
		* injuredState,
		* deathState,
		* pushState
		;
	PlayerState::State currentStateName;
	PlayerState::State prevStateName;

	BoxCollider collider;
	float collisionTime;
	SideCollision side;


private:
};