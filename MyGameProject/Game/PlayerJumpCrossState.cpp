﻿#include "PlayerJumpCrossState.h"

PlayerJumpCrossState::PlayerJumpCrossState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1028, "Resources/PlayerState/jump_cross_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1028), 1, 7, 0.1f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerJumpCrossState::~PlayerJumpCrossState()
{
}

void PlayerJumpCrossState::Render()
{
	PlayerState::Render();
}

void PlayerJumpCrossState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if(player->status == Player::Status::Jumping)
		player->SetVy(JUMP_SPEED*0.8);
	if (player->GetPosition().y >= player->lastposition.y + MAX_JUMP-3)
	{
		player->status = Player::Status::Falling;
		player->SetVy(-JUMP_SPEED*0.8);
	}
	// diem dung tam thoi
	

	// set time frame
	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.08);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.15f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.15f);
		break;
	case 3:
		m_Animation->SetDefaultTime(0.15f);
		break;
	default:
		m_Animation->SetDefaultTime(0.25f);
		break;
	}

	if (m_Animation->IsLastFrame(dt) && player->status != Player::Status::OnGround)
		player->SetState(Fall);
	PlayerState::Update(dt);
}

void PlayerJumpCrossState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(JUMP_ARROW))
	{
		countPressKey++;
	}

	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(JumpThrow);
		return;
	}

	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(JumpAttack);
		return;
	}

	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetVx(RUN_SPEED*1.1f);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetVx(-RUN_SPEED *1.1f);
		return;
	}
	player->SetVx(0);
}

void PlayerJumpCrossState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = playerData->player;
	if (player->status == Player::Status::OnGround
		&& (impactor->GetTag() == GROUND || impactor->GetTag() == STONE) && player->GetPrevStateName() != TouchGroud)
	{
		player->SetState(TouchGroud);
	}
}

PlayerState::State PlayerJumpCrossState::GetStateName()
{
	return JumpCross;
}

void PlayerJumpCrossState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-17);
	player->SetColliderRight(23);
	player->SetColliderTop(37);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
