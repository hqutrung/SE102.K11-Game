#include "PlayerDuckThrowState.h"

PlayerDuckThrowState::PlayerDuckThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1051, "Resources/PlayerState/duck_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1051), 1, 7, 0.08f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerDuckThrowState::~PlayerDuckThrowState()
{
}

void PlayerDuckThrowState::Render()
{
	PlayerState::Render();
}

void PlayerDuckThrowState::Update(float dt)
{

	auto player = playerData->player->GetInstance();
	player->SetVelocity(D3DXVECTOR2(0, 0));

	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Duck);
		playerData->state->GetAnimation()->SetCurrentFrame(4);
	}

	PlayerState::Update(dt);
}

void PlayerDuckThrowState::HandleInput()
{

	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(UP_ARROW))
		 {
		player->SetState(Idle);
		return;
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		return;
	}
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		return;
	}
	if (keyboard->GetKey(DOWN_ARROW))
		return;
}