#include "PlayerRunState.h"


PlayerRunState::PlayerRunState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1001, "Resources/PlayerState/run_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1001), 1, 14, 0.08f, D3DCOLOR_XRGB(255, 0,255));
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
	
	if (m_Animation->IsLastFrame(dt) == true)
	{
		m_Animation->countLoopFrame ++;
		m_Animation->SetCurrentFrame(3);
	}
	PlayerState::Update(dt);
	
}

void PlayerRunState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(THROW_ARROW) && player->GetState(RunThrow)->countPressKey == 1)
	{
		player->SetState(RunAttack);
		return;
	}
	//run -> attack

	if (keyboard->GetKeyDown(ATTACK_ARROW) && player->GetState(RunAttack)->countPressKey == 1)
	{
		player->SetState(RunAttack);
		return;
	}

	if (keyboard->GetKeyUp(ATTACK_ARROW))
	{
		countPressKey = 1;
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
	if (m_Animation->countLoopFrame > 1)
	{
		player->SetState(Slide);
		m_Animation->countLoopFrame = 1;
	}
	else
		player->SetState(Idle);
}

PlayerState::State PlayerRunState::GetStateName()
{
	return Run;
}
