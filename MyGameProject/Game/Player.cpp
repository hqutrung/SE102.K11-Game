#include "Player.h"
#include"Textures.h"
#include"PlayerIdleState.h"
#include"PlayerRunState.h"
#include"PlayerIdleAttackState.h"
#include"PlayerRunAttackState.h"
#include"PlayerDuckState.h"
#include"PlayerDuckAttackState.h"
#include"PlayerSlideState.h"
#include"PLayerLookUpState.h"
#include"PlayerLookUpAttackState.h"
#include"PlayerJumpState.h"
#include"PlayerFallState.h"
#include"PlayerJumpCrossState.h"
#include"PlayerJumpAttack.h"
#include"PlayerIdleThrowState.h"
#include"PlayerDuckThrowState.h"
#include"PlayerRunThrowState.h"
#include"PlayerJumpThrowState.h"
#include"PlayerClimbState.h"
#include"PlayerClimbAttackState.h"
#include"PlayerClimbThrowState.h"
#include"PlayerInjuredState.h"
#include"PlayerClimbJumpState.h"
#include"PlayerDeathState.h"

Player* Player::instance = NULL;

Player* Player::GetInstance()
{
	if (!instance)
		instance = new Player();
	return instance;
}

Player::Player()
{
	instance = this;
	Textures* textures = Textures::GetInstance();

	playerData = new PlayerData();
	playerData->player = this;


	idleState = new PlayerIdleState(playerData);
	runState = new PlayerRunState(playerData);
	idleAttackState = new PlayerIdleAttackState(playerData);
	runAttackState = new PlayerRunAttackState(playerData);
	duckState = new PlayerDuckState(playerData);
	duckAttackState = new PlayerDuckAttackState(playerData);
	slideState = new PlayerSlideState(playerData);
	lookUpState = new PlayerLookUpState(playerData);
	lookUpAttackState = new PlayerLookUpAttackState(playerData);
	jumpState = new PlayerJumpState(playerData);
	fallState = new PlayerFallState(playerData);
	jumpCrossState = new PlayerJumpCrossState(playerData);
	jumpAttackState = new PlayerJumpAttackState(playerData);
	idleThrowState = new PlayerIdleThrowState(playerData);
	duckThrowState = new PlayerDuckThrowState(playerData);
	runThrowState = new PlayerRunThrowState(playerData);
	jumpThrowState = new PlayerJumpThrowState(playerData);
	climbState = new PlayerClimbState(playerData);
	climbAttackState = new PlayerClimbAttackState(playerData);
	climbThrowState = new PlayerClimbThrowState(playerData);
	climbJumpState = new PlayerClimbJumpState(playerData);
	injuredState = new PlayerInjuredState(playerData);
	deathState = new PlayerDeathState(playerData);

	currentStateName = PlayerState::Idle;
	prevStateName = PlayerState::Idle;
	SetState(PlayerState::Idle);
	width = 37;
	height = 55;
	SetTag(PLAYER);
	SetType(Layer::PlayerType);

}

Player::~Player()
{
	delete idleState;
	idleState = NULL;
	delete runState;
	runState = NULL;
	delete idleAttackState;
	idleAttackState = NULL;
	delete runAttackState;
	runAttackState = NULL;
	delete duckState;
	duckState = NULL;
	delete duckAttackState;
	duckAttackState = NULL;
	delete lookUpState;
	lookUpState = NULL;
	delete lookUpAttackState;
	lookUpAttackState = NULL;
	delete jumpState;
	jumpState = NULL;
	delete fallState;
	fallState = NULL;
	delete jumpCrossState;
	jumpCrossState = NULL;
	delete jumpAttackState;
	jumpAttackState = NULL;
	delete idleThrowState;
	idleThrowState = NULL;
	delete duckThrowState;
	duckThrowState = NULL;
	delete runThrowState;
	runThrowState = NULL;
	delete	jumpThrowState;
	jumpThrowState = NULL;
	delete climbState;
	climbState = NULL;
	delete climbAttackState;
	climbAttackState = NULL;
	delete climbThrowState;
	climbThrowState = NULL;
	delete climbJumpState;
	climbThrowState = NULL;
	delete injuredState;
	climbThrowState = NULL;
	delete deathState;
	deathState = NULL;
	delete playerData;
	instance = NULL;
}

void Player::Update(float dt)
{
	Entity::Update(dt);
	if (playerData->state)
		playerData->state->Update(dt);
	DebugOut(L"y = %f\n", position.y);
}

void Player::Render()
{
	playerData->state->Render();
}

void Player::SetState(PlayerState::State state)
{
	if (playerData->state != NULL)
	{
		prevStateName = currentStateName;
	}
	switch (state) {
	case PlayerState::Idle:
		playerData->state = idleState;
		break;
	case PlayerState::Run:
		playerData->state = runState;
		break;
	case PlayerState::IdleAttack:
		playerData->state = idleAttackState;
		break;
	case PlayerState::RunAttack:
		playerData->state = runAttackState;
		break;
	case PlayerState::Duck:
		playerData->state = duckState;
		break;
	case PlayerState::DuckAttack:
		playerData->state = duckAttackState;
		break;
	case PlayerState::Slide:
		playerData->state = slideState;
		break;
	case PlayerState::LookUp:
		playerData->state = lookUpState;
		break;
	case PlayerState::LookUpAttack:
		playerData->state = lookUpAttackState;
		break;
	case PlayerState::Jump:
		playerData->state = jumpState;
		status = Jumping;
		break;
	case PlayerState::Fall:
		playerData->state = fallState;
		status = Falling;
		break;
	case PlayerState::JumpCross:
		playerData->state = jumpCrossState;
		status = Jumping;
		break;
	case PlayerState::JumpAttack:
		playerData->state = jumpAttackState;
		break;
	case PlayerState::IdleThrow:
		playerData->state = idleThrowState;
		break;
	case PlayerState::DuckThrow:
		playerData->state = duckThrowState;
		break;
	case PlayerState::RunThrow:
		playerData->state = runThrowState;
		break;
	case PlayerState::JumpThrow:
		playerData->state = jumpThrowState;
		break;
	case PlayerState::Climb:
		playerData->state = climbState;
		break;
	case PlayerState::ClimbAttack:
		playerData->state = climbAttackState;
		break;
	case PlayerState::ClimbThrow:
		playerData->state = climbThrowState;
		break;
	case PlayerState::ClimbJump:
		playerData->state = climbJumpState;
		break;
	case PlayerState::Injured:
		playerData->state = injuredState;
		break;
	case PlayerState::Death:
		playerData->state = deathState;
		break;
	}
	currentStateName = GetCurrentState()->GetStateName();
	playerData->state->ResetState();
}

void Player::HandleInput()
{
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyUp(ATTACK_ARROW))
	{
		idleAttackState->countPressKey = 1;
		runAttackState->countPressKey = 1;
		duckAttackState->countPressKey = 1;
		jumpAttackState->countPressKey = 1;
		lookUpAttackState->countPressKey = 1;
		climbAttackState->countPressKey = 1;
	}
	if (keyboard->GetKeyUp(THROW_ARROW))
	{
		idleThrowState->countPressKey = 1;
		runThrowState->countPressKey = 1;
		climbThrowState->countPressKey = 1;
		duckThrowState->countPressKey = 1;
	}
	if (this->playerData->state)
		playerData->state->HandleInput();
}


PlayerState* Player::GetCurrentState()
{
	return playerData->state;
}

PlayerState* Player::GetState(PlayerState::State state)
{
	switch (state) {
	case PlayerState::Idle:
		return idleState;
	case PlayerState::Run:
		return runState;
	case PlayerState::IdleAttack:
		return idleAttackState;
		break;
	case PlayerState::RunAttack:
		return runAttackState;
	case PlayerState::Duck:
		return duckState;
	case PlayerState::DuckAttack:
		return duckAttackState;
	case PlayerState::Slide:
		return slideState;
	case PlayerState::LookUp:
		return lookUpState;
	case PlayerState::LookUpAttack:
		return lookUpAttackState;
	case PlayerState::IdleThrow:
		return idleThrowState;
	case PlayerState::RunThrow:
		return runThrowState;
	case PlayerState::ClimbAttack:
		return climbAttackState;
	case PlayerState::ClimbThrow:
		return climbThrowState;
	case PlayerState::DuckThrow:
		return duckThrowState;
	}
}

void Player::SetColliderTop(int top)
{
	collider.top = top;
}

void Player::SetColliderLeft(int left)
{
	collider.left = left;
}

void Player::SetColliderBottom(int bottom)
{
	collider.bottom = bottom;
}

void Player::SetColliderRight(int right)
{
	collider.right = right;
}

BoxCollider Player::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	if (direction == LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
	return r;
}

void Player::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
	auto impactorRect = impactor->GetRect();
	auto impactorDir = impactor->GetMoveDirection();
	auto impactorTag = impactor->GetTag();
	float playerBottom = position.y - GetBigHeight() / 2.0 + collisionTime * dt * velocity.y;;

	D3DXVECTOR2 newVelocity = velocity;

	//if (impactor->GetType() == StaticType)
	//	if (side == Bottom) {

	//		if (round(playerBottom) == impactorRect.top && velocity.y <= 0) {
	//			newVelocity.y *= collisionTime;
	//		}
	//	}
		//else {

		//	bool specialWall = ((int)impactorRect.right - (int)impactorRect.left <= 16) && impactorTag == GROUND;

		//	bool canPassLeft = specialWall && velocity.x < 0 && impactorDir == RightToLeft;
		//	bool canPassRight = specialWall && velocity.x > 0 && impactorDir == RightToLeft;

		//	float slashCaseLeft = (impactorRect.left - GetBody().right) / (dt * velocity.x);
		//	float slashCaseRight = (impactorRect.right - GetBody().left) / (dt * velocity.x);

		//	if (currentState == PlayerState::Slash) {
		//		//BUG
		//		if (collisionTime == 0)
		//			collisionTime = min(slashCaseLeft, slashCaseRight);
		//		if (collisionTime > 1)
		//			collisionTime = 0;
		//	}

		//	float playerLeft = GetBody().left + velocity.x * collisionTime * dt;
		//	float playerRight = GetBody().right + velocity.x * collisionTime * dt;

		//	if ((side == Left && velocity.x < 0 && impactorRect.right == round(playerLeft)) || ((side == Right && velocity.x > 0) && impactorRect.left == round(playerRight))) {
		//		if (impactorRect.top > round(playerBottom) && impactorRect.bottom <= round(playerBottom)) {

		//			if (!canPassLeft || !canPassRight)
		//				newVelocity.x *= collisionTime;

		//			if ((int)impactorRect.top - (int)impactorRect.bottom > 32) {
		//				//if (GetRect().bottom < impactorRect.bottom)
		//				//	return;
		//				int sign = -1;
		//				if (impactorTag == LADDER)
		//					sign = 1;
		//				bool climbToWall = (impactorDir != RightToLeft && velocity.x < 0) || (impactorDir != LeftToRight && velocity.x > 0);
		//				bool climbToLadder = (sign == 1) && (playerBottom + LADDER_OFFSET < impactorRect.top) && climbToWall;
		//				climbToWall = climbToWall && (sign == -1) && velocity.y != 0;
		//				if (climbToWall || climbToLadder) {
		//					SetMoveDirection(impactor->GetPosition().x > position.x ? LeftToRight : RightToLeft);
		//					SetState(PlayerState::Climb, sign * impactorRect.top);
		//				}
		//			}
		//		}

		//	}
		//}

	velocity = newVelocity;

	playerData->state->OnCollision(impactor, side, collisionTime, dt);
}
