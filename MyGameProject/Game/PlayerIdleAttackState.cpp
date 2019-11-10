#include "PlayerIdleAttackState.h"

PlayerIdleAttackState::PlayerIdleAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1002, "Resources/PlayerState/aladinidleattack.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1002), 1, 5, 0.06f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerIdleAttackState::~PlayerIdleAttackState()
{
}

void PlayerIdleAttackState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if(playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		p = D3DXVECTOR3(player->GetPosition().x - (82 / 2 - 44 / 2), player->GetPosition().y + (74 / 2 - 55 / 2), 0);
	else 
		p = D3DXVECTOR3(player->GetPosition().x + (82 / 2 - 44 / 2), player->GetPosition().y + (74 / 2 - 55 / 2), 0);
	m_Animation->Render( p , BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
	 
}

void PlayerIdleAttackState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		playerData->player->SetState(Idle);
	}
	PlayerState::Update(dt);
}

void PlayerIdleAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	/*if (keyboard->GetKey(ATTACK_ARROW))
	{
		return;
	}*/
}
