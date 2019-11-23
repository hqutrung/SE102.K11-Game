#include "PlayerIdleThrowState.h"

PlayerIdleThrowState::PlayerIdleThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1030, "Resources/PlayerState/idle_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1030), 1, 8, 0.06f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerIdleThrowState::~PlayerIdleThrowState()
{
}

void PlayerIdleThrowState::Render()
{
	PlayerState::Render();

}

void PlayerIdleThrowState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		playerData->player->SetState(Idle);
	}

	PlayerState::Update(dt);
}

void PlayerIdleThrowState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	
	if (keyboard->GetKeyDown(THROW_ARROW))
	{
		countPressKey++;
		return;
	}

	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetState(Run);
		return;
	}

}
