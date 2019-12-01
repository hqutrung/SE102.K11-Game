#include "PlayerClimbThrowState.h"

PlayerClimbThrowState::PlayerClimbThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1256, "Resources/PlayerState/climb_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1256), 1, 6, 0.06f, D3DCOLOR_XRGB(255, 0, 255));

}

void PlayerClimbThrowState::Render()
{
	PlayerState::Render();
}

void PlayerClimbThrowState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));


	if (m_Animation->IsLastFrame(dt))
	{
		playerData->player->SetState(Climb);
	}

	PlayerState::Update(dt);
}

void PlayerClimbThrowState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(UP_ARROW) || keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Climb);
		return;
	}
	if (keyboard->GetKeyDown(THROW_ARROW) || keyboard->GetKey(THROW_ARROW))
	{
		countPressKey++;
	}
}

PlayerState::State PlayerClimbThrowState::GetStateName()
{
	return ClimbThrow;
}

void PlayerClimbThrowState::ResetState()
{
	PlayerState::ResetState();
}
