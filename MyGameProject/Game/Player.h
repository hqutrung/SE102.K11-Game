#pragma once
#include "Entity.h"
#include "PlayerData.h"
#include "PlayerState.h"

class Player : public Entity {
public:


	static Player* GetInstance();
	Player();
	~Player();
	void Update(float dt) override;
	void Render() override;
	void SetState(PlayerState::State name);
	void HandleInput();
	
	PlayerState* GetState(PlayerState::State name);
	PlayerState::State GetNameCurrentState() { return nameCurrentState; }
	PlayerState::State GetNamePrevState() { return namePrevState; }
	// sử dụng cho State Jump
	float GetPre_Y_Position() { return Pre_Y_Position; };
	void SetPre_Y_Position(float y) { Pre_Y_Position = y; };
	bool IsJump;
	//


	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	//BoxCollider GetRect();
	//BoxCollider GetBigBound();
	//BoxCollider GetBody();
	//PlayerState::State GetState();
	//float GetBigWidth() override;
	//float GetBigHeight() override;
	//float GetWidth() override;
	//float GetHeight() override;
	//void SetActive(bool active);
	//void OnFalling();
	//void SetColliderTop(int top);
	//void SetColliderLeft(int left);
	//void SetColliderBottom(int bottom);
	//void SetColliderRight(int right);
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
		* idleThrowState
		;
	PlayerState::State nameCurrentState;
	PlayerState::State namePrevState;
	BoxCollider collider;
	float collisionTime;

	float Pre_Y_Position=0;
private:
};