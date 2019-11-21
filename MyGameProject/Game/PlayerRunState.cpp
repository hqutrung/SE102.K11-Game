#include "PlayerRunState.h"


PlayerRunState::PlayerRunState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1001, "Resources/PlayerState/run.png", D3DCOLOR_XRGB(106, 148, 189));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1001), 1, 14, 0.07f, D3DCOLOR_XRGB(106, 148, 189));
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if (playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		p = D3DXVECTOR3(player->GetPosition().x - (72 / 2 - 44 / 2), player->GetPosition().y + (61 / 2 - 55 / 2), 0);
	else
		p = D3DXVECTOR3(player->GetPosition().x + (72 / 2 - 44 / 2), player->GetPosition().y + (61 / 2 - 55 / 2), 0);
	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

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
		m_Animation->abc = 1;
		m_Animation->SetCurrentFrame(2);
	}
	PlayerState::Update(dt);
	
}

void PlayerRunState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();


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
	if (m_Animation->abc == 1)
	{
		player->SetState(Slide);
		m_Animation->abc = 0;
	}
	else
		player->SetState(Idle);
}

PlayerState::State PlayerRunState::GetStateName()
{
	return Run;
}
