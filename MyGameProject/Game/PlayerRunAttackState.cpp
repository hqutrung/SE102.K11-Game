#include "PlayerRunAttackState.h"

PlayerRunAttackState::PlayerRunAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1003, "Resources/PlayerState/run_attack_after.png", D3DCOLOR_XRGB(255,0,255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1003), 1, 6, 0.08, D3DCOLOR_XRGB(255,0,255));

}

PlayerRunAttackState::~PlayerRunAttackState()
{
}

void PlayerRunAttackState::Render()
{
	PlayerState::Render();
}

void PlayerRunAttackState::Update(float dt)
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

	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.05f);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.05f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.1f);
		break;
	case 3:
		m_Animation->SetDefaultTime(0.1f);
		break;
	case 4:
		m_Animation->SetDefaultTime(0.1f);
		break;
	default:
		m_Animation->SetDefaultTime(0.05f);
		break;
	}
	
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Run);
	}

	PlayerState::Update(dt);
}

void PlayerRunAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}
	if (keyboard->GetKey(THROW_ARROW) || keyboard->GetKeyDown(THROW_ARROW))
	{
		player->SetState(RunThrow);
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
	player->SetState(Run);
}

void PlayerRunAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerRunAttackState::GetStateName()
{
	return RunAttack;
}

void PlayerRunAttackState::ResetState(int dummy)
{
}
