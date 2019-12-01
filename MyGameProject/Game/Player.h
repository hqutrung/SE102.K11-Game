#pragma once
#include "Entity.h"
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
	void SetState(PlayerState::State state);

	void HandleInput();

	PlayerState* GetCurrentState();
	PlayerState* GetState(PlayerState::State state);

	PlayerState::State GetPrevStateName() { return prevStateName; }
	// sử dụng cho State Jump
	Status status;
	//
	Status status;

	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);

	BoxCollider GetRect();
	BoxCollider GetBody();
	float GetBigWidth() override;
	float GetBigHeight() override;
	float GetWidth() override;
	float GetHeight() override;

	void SetActive(bool active);
	void OnFalling();

	void SetMoveDirection(Entity::MoveDirection dir) override;

	//void OnImmortal();
	//void OffImmortal();

	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	

	//bool isImmortal;
	//float immortalTime;
	bool checkGroundInFrame;
	float timeOnAir;

	//bool renderPreviousFrame;
	float _LegY = 800;

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
		* deathState
		;
	PlayerState::State currentStateName;
	PlayerState::State prevStateName;

	BoxCollider collider;
	float collisionTime;
	SideCollision side;


private:
};