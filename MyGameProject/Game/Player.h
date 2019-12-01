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

	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	BoxCollider GetRect();


	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	//BoxCollider GetBigBound();
	//BoxCollider GetBody();
	//PlayerState::State GetState();
	//float GetBigWidth() override;
	//float GetBigHeight() override;
	//float GetWidth() override;
	//float GetHeight() override;
	//void SetActive(bool active);
	//void OnFalling();

	//void SetMoveDirection(Entity::EntityDirection dir) override;
	//void InjuredByOther(Entity* impactor);
	//void OnImmortal();
	//void OffImmortal();
	//void CheckForUseItem();
	//void ThrowShuriken();
	//void ThrowBigShuriken();
	//void ThrowFlames();
	//virtual BoxCollider GetCollider();
	//Status status;

	//bool isImmortal;
	//bool checkGroundInFrame;
	//float timeOnAir;
	//float immortalTime;

	////check for immortal
	//bool renderPreviousFrame;
	float _LegY = 800;
	//cc
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


private:
};