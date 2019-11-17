#include "PlayerIdleThrowState.h"

PlayerIdleThrowState::PlayerIdleThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1030, "Resources/PlayerState/throw.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1030), 1, 6, 0.06f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerIdleThrowState::~PlayerIdleThrowState()
{
}

void PlayerIdleThrowState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if (playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		p = D3DXVECTOR3(player->GetPosition().x - (46 / 2 - 44 / 2), player->GetPosition().y + (60 / 2 - 55 / 2), 0);
	else
		p = D3DXVECTOR3(player->GetPosition().x + (46 / 2 - 44 / 2), player->GetPosition().y + (60 / 2 - 55 / 2), 0);
	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

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
