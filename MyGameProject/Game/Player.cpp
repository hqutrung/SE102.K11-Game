#include "Player.h"
#include"PlayerIdleState.h"
#include"PlayerRunState.h"
#include"PlayerIdleAttackState.h"
#include"PlayerRunAttackState.h"
#include"PlayerDuckState.h"
#include"PlayerDuckAttackState.h"
#include"PlayerSlideState.h"
#include"Textures.h"
#include"PLayerLookUpState.h"
#include"PlayerLookUpAttackState.h"
#include"PlayerJumpState.h"
#include"PlayerFallState.h"
#include"PlayerJumpCrossState.h"
#include"PlayerJumpAttack.h"
#include"PlayerIdleThrowState.h"
#include"PlayerDuckThrowState.h"
#include"PlayerRunThrowState.h"

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

	nameCurrentState = PlayerState::Idle;
	namePrevState = PlayerState::Idle;
	SetState(PlayerState::Idle);
	width = 44;
	height = 55;

	Pre_Y_Position = position.y;
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
	delete idleThrowState;
	idleThrowState = NULL;
	delete playerData;
	instance = NULL;
}

void Player::Update(float dt)
{
	Entity::Update(dt);
	if (playerData->state)
		playerData->state->Update(dt);
}

void Player::Render()
{
	playerData->state->Render();
}

void Player::SetState(PlayerState::State name)
{

	namePrevState = nameCurrentState;
	nameCurrentState = name;

	switch (name) {
	case PlayerState::Idle:
		playerData->state = idleState;
		break;
	case PlayerState::Run:
		playerData->state = runState;
		if (namePrevState == PlayerState::RunAttack)
			return;
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
		Pre_Y_Position = position.y;
		IsJump = true;
		break;
	case PlayerState::Fall:
		playerData->state = fallState;
		break;
	case PlayerState::JumpCross:
		playerData->state = jumpCrossState;
		Pre_Y_Position = position.y;
		IsJump = true;
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
	}

	playerData->state->GetAnimation()->ResetAnimation();
}

void Player::HandleInput()
{
auto keyboard=	KeyBoard::GetInstance();

if (keyboard->GetKeyUp(ATTACK_ARROW))
{
	idleAttackState->countPressKey = 1;
	runAttackState->countPressKey = 1;
	duckAttackState->countPressKey = 1;
	jumpAttackState->countPressKey = 1;
	lookUpAttackState->countPressKey = 1;
}
if (keyboard->GetKeyUp(THROW_ARROW))
{
	idleThrowState->countPressKey = 1;
	runThrowState->countPressKey = 1;
}
	if (this->playerData->state)
		playerData->state->HandleInput();
}


PlayerState* Player::GetState(PlayerState::State name)
{
	switch (name) {
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
	case PlayerState::IdleThrow :
		return idleThrowState;
	case PlayerState::RunThrow:
		return runThrowState;
	}
}
