#include "PlayerLookUpAttackState.h"

PlayerLookUpAttackState::PlayerLookUpAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1020, "Resources/PlayerState/lookupattack .png", D3DCOLOR_XRGB(106, 148, 189));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1020), 1, 11, 0.1f, D3DCOLOR_XRGB(106, 148, 189));

}

PlayerLookUpAttackState::~PlayerLookUpAttackState()
{
}

void PlayerLookUpAttackState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if (playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		p = D3DXVECTOR3(player->GetPosition().x, player->GetPosition().y + (86 / 2 - 55 / 2), 0);
	else
		p = D3DXVECTOR3(player->GetPosition().x , player->GetPosition().y + (86 / 2 - 55 / 2), 0);
	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void PlayerLookUpAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	player->SetVelocity(D3DXVECTOR2(0, 0));
	PlayerState::Update(dt);
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Idle);
		playerData->state->GetAnimation()->SetCurrentFrame(2);
	}
}

void PlayerLookUpAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Duck);
		return;
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetState(Run);
		return;
	}
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetState(Run);
		return;
	}
	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}
	if (keyboard->GetKey(UP_ARROW))
	{
		return;
	}
}

PlayerState:: State PlayerLookUpAttackState::GetState()
{
	return LookUpAttack;
}
