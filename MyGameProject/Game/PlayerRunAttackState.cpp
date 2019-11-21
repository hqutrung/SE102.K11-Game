﻿#include "PlayerRunAttackState.h"

PlayerRunAttackState::PlayerRunAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1003, "Resources/PlayerState/runattack.png", D3DCOLOR_XRGB(106, 148, 189));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1003), 1, 6, 0.08, D3DCOLOR_XRGB(106, 148, 189));

}

PlayerRunAttackState::~PlayerRunAttackState()
{
}

void PlayerRunAttackState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if (playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		p = D3DXVECTOR3(player->GetPosition().x - (73 / 2 - 44 / 2), player->GetPosition().y + (60 / 2 - 55 / 2), 0);
	else
		p = D3DXVECTOR3(player->GetPosition().x + (73 / 2 - 44 / 2), player->GetPosition().y + (60 / 2 - 55 / 2), 0);
	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

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
	player->SetState(Idle);
}

PlayerState::State PlayerRunAttackState::GetStateName()
{
	return RunAttack;
}
