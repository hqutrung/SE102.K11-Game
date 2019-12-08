#include "Player.h"
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
#include "CollisionDetector.h"
#include"PlayerPushState.h"
#include"PlayerTouchGroundState.h"



Player* Player::instance = NULL;

Player* Player::GetInstance()
{
	if (!instance)
		instance = new Player();
	return instance;
}

Player::Player() : Entity()
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
	pushState = new PlayerPushState(playerData);
	touchGroundState = new PlayerTouchGroundState(playerData);

	currentStateName = PlayerState::Idle;
	prevStateName = PlayerState::Idle;
	SetState(PlayerState::Idle);
	SetTag(PLAYER);
	SetType(PlayerType);
	SetStatic(false);
	SetActive(true);
	status = OnGround;

	isInjured = false;
	lastposition = position;
	width = 37;
	height = 55;
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
	delete pushState;
	pushState = NULL;
	delete touchGroundState;
	touchGroundState = NULL;

	delete playerData;
	instance = NULL;

}

void Player::Update(float dt)
{


	Entity::Update(dt);

	if (playerData->state)
		playerData->state->Update(dt);
	timeInjured += dt;
	countFrame++;
	isInjured = false;

}

void Player::Render()
{
	if (timeInjured > 0 && timeInjured < 0.5f)
	{
		if (countFrame % 6 != 0)
		{
			playerData->state->Render();
		}
	}
	else {
		playerData->state->Render();
	}

}

void Player::SetState(PlayerState::State state, int dummy)
{
	if (playerData->state != NULL)
		prevStateName = currentStateName;

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
		status = Climbing;
		playerData->state = climbState;
		break;
	case PlayerState::ClimbAttack:
		status = Climbing;
		playerData->state = climbAttackState;
		break;
	case PlayerState::ClimbThrow:
		status = Climbing;
		playerData->state = climbThrowState;
		break;
	case PlayerState::ClimbJump:
		status = Jumping;
		lastposition = position;
		playerData->state = climbJumpState;
		break;
	case PlayerState::Injured:
		playerData->state = injuredState;
		break;
	case PlayerState::Death:
		playerData->state = deathState;
		break;
	case PlayerState::Push:
		playerData->state = pushState;
		break;
	case PlayerState::TouchGroud:
		status = OnGround;
		playerData->state = touchGroundState;
		break;
	}
	currentStateName = GetCurrentState()->GetStateName();
	playerData->state->ResetState(dummy);
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
	if (keyboard->GetKeyUp(JUMP_ARROW))
	{
		jumpState->countPressKey = 1;
		jumpCrossState->countPressKey = 1;
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
	case PlayerState::Jump:
		return jumpState;
	case PlayerState::JumpCross:
		return jumpCrossState;
	case PlayerState::ClimbAttack:
		return climbAttackState;
	case PlayerState::ClimbThrow:
		return climbThrowState;
	case PlayerState::DuckThrow:
		return duckThrowState;
	case PlayerState::Push:
		return pushState;
	case PlayerState::TouchGroud:
		return touchGroundState;
	case PlayerState::Fall:
		return fallState;
	case PlayerState::ClimbJump:
		return climbJumpState;
	case PlayerState::JumpAttack:
		return jumpAttackState;
	case PlayerState::JumpThrow:
		return jumpThrowState;
	case PlayerState::Injured:
		return injuredState;
	}
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

BoxCollider Player::GetBody()
{
	return playerData->state->GetBody();
}

BoxCollider Player::GetBigBound() {
	BoxCollider box;
	if (GetMoveDirection() == Player::MoveDirection::LeftToRight)
		box = BoxCollider(position.y + 25, position.x - 16, position.x + 19, position.y - 24);
	else
		box = BoxCollider(position.y + 25, position.x - 19, position.x + 16, position.y - 24);
	return box;
}

float Player::GetBigWidth()
{
	return Entity::GetWidth();
}

float Player::GetBigHeight()
{
	return Entity::GetHeight();
}

float Player::GetWidth()
{
	return collider.right - collider.left;
}

float Player::GetHeight()
{
	return collider.top - collider.bottom;
}

void Player::SetActive(bool active)
{
	/*if (active == false) {
		playerData->state = injuredState;
		DataManager::SetPlayerDead();
	}
	else {*/
	Entity::SetActive(true);
	//}
}

void Player::SetStatus(enum Status status)
{
	this->status = status;
}

Player::Status Player::GetStatus()
{
	return status;
}

void Player::OnFalling()
{
	SetState(PlayerState::Fall);
}

void Player::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto impactorRect = impactor->GetRect();
	auto impactorDir = impactor->GetMoveDirection();
	auto impactorTag = impactor->GetTag();

	// Rect tiep theo cua state hien tai
	float playerBottom = GetRect().bottom + collisionTime * dt * velocity.y;
	float playerRight = GetRect().right + collisionTime * dt * velocity.x;
	float playerLeft = GetRect().left + collisionTime * dt * velocity.x;
	float playerTop = GetRect().top + collisionTime * dt * velocity.y;
	//vitri ke tiep
	float newPosX = position.x + collisionTime * dt * velocity.x;
	float newPosY = position.y + collisionTime * dt * velocity.y;

	//Debug
	if (impactor->GetTag() == STONE)
		position.x = position.x;

	// Rect tiep theo cua body
	float rPlayer = GetBigBound().right + collisionTime * dt * velocity.x;
	float lPlayer = GetBigBound().left + collisionTime * dt * velocity.x;
	float tPlayer = GetBigBound().top + collisionTime * dt * velocity.y;
	float bPlayer = GetBigBound().bottom + collisionTime * dt * velocity.y;


	D3DXVECTOR2 newVelocity = velocity;

	// stand on Ground
	if (side == Entity::SideCollision::Bottom && status != Jumping && status != Climbing)
	{
		if ((impactor->GetTag() == GROUND || (impactor->GetTag() == STONE && impactor->IsCollidable())) && round(playerBottom) == impactorRect.top && velocity.y < 0
			&& Support::IsContainedIn(position.x, impactorRect.left - 4, impactorRect.right + 4))
		{
			status = OnGround;
			newVelocity.y *= collisionTime;
			lastposition = D3DXVECTOR3(position.x, position.y + newVelocity.y * dt, 0);

		}
	}
	// va cham tuong (WALL)
	if (impactor->GetTag() == WALL)
	{
		newVelocity.x *= collisionTime;

		if ((side == Right && round(rPlayer) == impactorRect.left || side == Left && round(lPlayer) == impactorRect.right)
			&& velocity.x != 0
			&& (bPlayer >= impactor->GetRect().bottom && bPlayer < impactor->GetRect().top))
		{
			if (GetCurrentState()->GetStateName() == PlayerState::State::Run || GetCurrentState()->GetStateName() == PlayerState::State::RunAttack || GetCurrentState()->GetStateName() == PlayerState::State::RunThrow)
			{
				lastposition = D3DXVECTOR3(position.x + newVelocity.x * dt, position.y, 0);
				SetState(PlayerState::Push);
			}
		}
	}





	// ItemType
	if (impactor->GetType() == ItemType)
	{
		impactor->SetActive(false);
	}
	else if (impactor->GetTag() == BLUEVASE)
	{
		impactor->SetIsCollidable(true);
	}
	else if (impactor->GetTag() == EXITPORT)
		exit(0);
	// !OnGround rớt đất
	else if (status == OnGround && side == SideCollision::Bottom && (impactor->GetTag() == GROUND || (impactor->GetTag() == STONE)) && velocity.y == 0)
	{
		if (Support::IsContainedIn(position.x, impactorRect.left - 4, impactorRect.right + 4) == false || !impactor->IsCollidable())
		{
			SetVy(-JUMP_SPEED);
			SetState(PlayerState::Fall);
			status = Falling;
		}
	}
	if (impactor->GetTag() == CHAINE)
		int x = 0;

	// climb
	if (impactor->GetTag() == CHAINE)
	{
		if (side != Top
			&& status == Falling
			//	&& round(newPosX) == impactor->GetPosition().x
			&& Support::IsContainedIn(round(newPosX), impactor->GetPosition().x - 2, impactor->GetPosition().x + 2)
			&& Support::IsContainedIn(bPlayer, impactorRect.bottom, impactorRect.top - 84 - 10))
		{
			newVelocity.x *= collisionTime;
			status = Climbing;
			SetState(PlayerState::Climb);
		}
	}


	if (impactor->GetType() == EnemyType)
		int x = 0;
	// Injured

	if ((impactor->GetTag() == SPIKE || impactor->GetTag() == BALL || impactor->GetType() == EnemyType) 
		&& impactor->IsCollidable() && IsCollidable() 
		&& collisionTime == 0)
	{
		isInjured = true;
		timeInjured = 0;
	}

	velocity = newVelocity;
	playerData->state->OnCollision(impactor, side, collisionTime, dt);
}

void Player::InjuredByOther(Entity* impactor)
{
	SetState(PlayerState::Injured);
	//DataManager::MinusHealth(impactor->GetTag());
}
