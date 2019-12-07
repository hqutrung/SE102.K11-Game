#pragma once
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

	// sử dụng cho State Jump
	D3DXVECTOR3 lastposition;
	bool isClaimWall = false;
	Status status;
	void SetStatus(Status status);
	Player::Status GetStatus();

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

	BoxCollider GetRect();
	BoxCollider GetBody();
	BoxCollider GetBigBound();

	float GetBigWidth() override;
	float GetBigHeight() override;
	float GetWidth() override;
	float GetHeight() override;

	void SetActive(bool active);
	void OnFalling();

	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60) override;
	void InjuredByOther(Entity* impactor);

	// Bat tu
	//void OnImmortal();
	//void OffImmortal();
	//bool isImmortal;
	//float immortalTime;

	//bool checkGroundInFrame;
	//float timeOnAir;

	//bool renderPreviousFrame;
	bool isInjured = false;
	float timeInjured = 0.5f;
	int countFrame=0;

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
		* pushState,
		* touchGroundState;

		;
	PlayerState::State currentStateName;
	PlayerState::State prevStateName;

	float collisionTime;
	SideCollision side;

private:
};