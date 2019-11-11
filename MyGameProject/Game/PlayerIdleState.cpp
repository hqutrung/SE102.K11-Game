#include "PlayerIdleState.h"

PlayerIdleState::PlayerIdleState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1000, "Resources/PlayerState/aladinidle.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1000), 1, 7, 0.1f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Render()
{
	PlayerState::Render();
}

void PlayerIdleState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->GetCurrentFrameID() == 3 || m_Animation->GetCurrentFrameID() == 6)
		m_Animation->SetDefaultTime(1.0f);
	else
		m_Animation->SetDefaultTime(0.1f);

	PlayerState::Update(dt);
}


void PlayerIdleState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	
	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(IdleThrow);
		return;
	}
	
	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(Jump);
		return;
	}
	
	if (keyboard->GetKey(UP_ARROW))
	{
		player->SetState(LookUp);
		return;
	}

	// Nếu nhấn down-arrow thì duck
	if (keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Duck);
		return;
	}



	//====idle->idle_attack

	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(IdleAttack);
		return;
	}

	//=== idle->run 

	if (keyboard->GetKey(LEFT_ARROW) && keyboard->GetKey(RIGHT_ARROW))
	{
		return;
	}
	// Nếu ấn right-arrow thì chạy qua phải

	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetState(Run);
		player->SetVy(0);
		return;
	}

	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetState(Run);
		player->SetVy(0);
		return;
	}
}

