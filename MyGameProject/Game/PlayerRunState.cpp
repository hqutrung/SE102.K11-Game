#include "PlayerRunState.h"


PlayerRunState::PlayerRunState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1001, "Resources/PlayerState/run.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1001), 1, 11, 0.07f, D3DCOLOR_XRGB(255, 255, 255));
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::Render()
{
	PlayerState::Render();
}

void PlayerRunState::Update(float dt)
{
	auto player = playerData->player->GetInstance();

	if (player->GetMoveDirection() == Entity::MoveDirection::LeftToRight)
	{
		player->SetVx(RUN_SPEED);
	}
	else {
		if (player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		{
			player->SetVx(-RUN_SPEED);
		}
	}

	if (m_Animation->IsLastFrame(dt)==true)
	{
		m_Animation->abc = 1;
	}

	PlayerState::Update(dt);
}

void PlayerRunState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();


	//run -> attack

	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(RunAttack);
		return;
	}
	//run->jumpcross
	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(JumpCross);
		return;
	}

	// run->idle
	if (keyboard->GetKey(LEFT_ARROW) && keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetState(Idle);
		return;
	}
	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		return;
	}
	if (m_Animation->abc == 1)
	{
		player->SetState(Slide);
		m_Animation->abc = 0;
	}
	else
		player->SetState(Idle);
}
