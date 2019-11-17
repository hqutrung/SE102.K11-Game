#include "PlayerDuckAttackState.h"

PlayerDuckAttackState::PlayerDuckAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1011, "Resources/PlayerState/duckAttack.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1011), 1, 7, 0.08f, D3DCOLOR_XRGB(255, 255, 255));

}
PlayerDuckAttackState::~PlayerDuckAttackState()
{
}

void PlayerDuckAttackState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if (playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		p = D3DXVECTOR3(player->GetPosition().x - (100/ 2 - 44 / 2), player->GetPosition().y - (55 / 2 - 31 / 2), 0);
	else
		p = D3DXVECTOR3(player->GetPosition().x + (100 / 2 - 44 / 2), player->GetPosition().y - (55 / 2 - 31 / 2), 0);
	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

}

void PlayerDuckAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	player->SetVelocity(D3DXVECTOR2(0, 0));
	PlayerState::Update(dt);
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Duck);
		playerData->state->GetAnimation()->SetCurrentFrame(3);
	}
}

void PlayerDuckAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

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

PlayerState::State PlayerDuckAttackState::GetState()
{
	return DuckAttack;
}
