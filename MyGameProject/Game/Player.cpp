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

void Player::SetState(PlayerState::State state)
{
	switch (state) {
	case PlayerState::Idle:
		playerData->state = idleState;
		nameCurrentState = PlayerState::Idle;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::Run:
		playerData->state = runState;
		nameCurrentState = PlayerState::Run;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::IdleAttack:
		playerData->state = idleAttackState;
		nameCurrentState = PlayerState::IdleAttack;
		playerData->state->GetAnimation()->ResetAnimation();
		break;

	case PlayerState::RunAttack:
		playerData->state = runAttackState;
		nameCurrentState = PlayerState::RunAttack;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::Duck:
		playerData->state = duckState;
		nameCurrentState = PlayerState::Duck;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::DuckAttack:
		playerData->state = duckAttackState;
		nameCurrentState = PlayerState::DuckAttack;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::Slide:
		playerData->state = slideState;
		nameCurrentState = PlayerState::Slide;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::LookUp:
		playerData->state = lookUpState;
		nameCurrentState = PlayerState::LookUp;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::LookUpAttack:
		playerData->state = lookUpAttackState;
		nameCurrentState = PlayerState::LookUpAttack;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::Jump:
		playerData->state = jumpState;
		nameCurrentState = PlayerState::Jump;
		Pre_Y_Position = position.y;
		IsJump = true;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::Fall:
		playerData->state = fallState;
		nameCurrentState = PlayerState::Fall;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::JumpCross:
		playerData->state = jumpCrossState;
		nameCurrentState = PlayerState::JumpCross;
		Pre_Y_Position = position.y;
		IsJump = true;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::JumpAttack:
		playerData->state = jumpAttackState;
		nameCurrentState = PlayerState::JumpAttack;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	case PlayerState::IdleThrow:
		playerData->state = idleThrowState;
		nameCurrentState = PlayerState::IdleThrow;
		playerData->state->GetAnimation()->ResetAnimation();
		break;
	}
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
		break;
	case PlayerState::Run:
		return runState;
		break;
	case PlayerState::IdleAttack:
		return idleAttackState;
		break;

	case PlayerState::RunAttack:
		return runAttackState;
		break;
	case PlayerState::Duck:
		return duckState;
		break;
	case PlayerState::DuckAttack:
		return duckAttackState;
		break;
	case PlayerState::Slide:
		return slideState;
		break;
	case PlayerState::LookUp:
		return lookUpState;
		break;
	}
}
