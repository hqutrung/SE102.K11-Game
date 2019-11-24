﻿#include "PlayerJumpAttack.h"

PlayerJumpAttackState::PlayerJumpAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1029, "Resources/PlayerState/jump_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1029), 1, 7, 0.07f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerJumpAttackState::~PlayerJumpAttackState()
{
}

void PlayerJumpAttackState::Render()
{
	PlayerState::Render();
}

void PlayerJumpAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if (player->GetPosition().y > player->_LegY + 68)
	{
		player->IsJump = false;
	}

	if (player->GetPosition().y < player->_LegY + 68 && player->IsJump == true)
	{
		player->SetVy(JUMP_SPEED * 1.1);
	}
	else {
		player->SetVy(-JUMP_SPEED * 1.1);
	}

	if (player->GetPosition().y < player->_LegY - 10)
	{
		player->SetPosition(player->GetPosition().x, player->_LegY);
		player->SetState(Idle);
	}
	if (m_Animation->IsLastFrame(dt))
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID() - 1);


	PlayerState::Update(dt);
}

void PlayerJumpAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetVx(RUN_SPEED / 1.1f);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetVx(- RUN_SPEED / 1.1f);
		return;
	}
	player->SetVx(0);
}

PlayerState::State PlayerJumpAttackState::GetStateName()
{
	return JumpAttack;
}
