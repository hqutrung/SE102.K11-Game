#pragma once
#include "Entity.h"
#include "DemoObjectData.h"
#include "DemoObjectState.h"

class DemoObject : public Entity
{

protected:
	static DemoObject* instance;
	DemoObjectData* demoObjectData;
	DemoObjectState* runningState, *idleState;
		//* slashState,
		//* crouchState,
		//* jumpState,
		//* crouchSlashState,
		//* climbState,
		//* useItemState,
		//* injuredState;

	DemoObjectState::State currentState;
	BoxCollider collider;
	float collisionTime;				// Thoi gian va cham
	SideCollision side;

public:
	/*enum Status {
		Jumping,
		Falling,
		OnGround,
		Climbing
	};*/

	//Status status;

	/*bool isImmortal;
	bool checkGroundInFrame;
	float timeOnAir;
	float immortalTime;*/

	////check for immortal
	//bool renderPreviousFrame;

	static DemoObject* GetInstance();

	DemoObject();
	~DemoObject();

	void Update(float dt) override;
	void Render() override;
	void HandleInput();

	//void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	//void OnFalling();
	//void InjuredByOther(Entity* impactor);

	void SetState(DemoObjectState::State name, int dummy = 0);
	DemoObjectState::State GetState();

	//BoxCollider GetCollider();

	//BoxCollider GetRect();
	//BoxCollider GetBigBound();
	//BoxCollider GetBody();

	//void SetActive(bool active) override;

	////Get collilder width
	//float GetWidth() override;
	//float GetBigWidth() override;

	////Get collider height;
	//float GetHeight() override;
	//float GetBigHeight() override;

	//void SetColliderTop(float top);
	//void SetColliderLeft(float left);
	//void SetColliderBottom(float bottom);
	//void SetColliderRight(float right);

	void SetMoveDirection(Entity::MoveDirection dir);


	//void OnImmortal();
	//void OffImmortal();

	/*void CheckForUseItem();
	void ThrowShuriken();
	void ThrowBigShuriken();
	void ThrowFlames();*/

};
