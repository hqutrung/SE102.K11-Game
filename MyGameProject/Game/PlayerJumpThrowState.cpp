#include "PlayerJumpThrowState.h"

PlayerJumpThrowState::PlayerJumpThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1036, "Resources/PlayerState/jump_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1036), 1, 7, 0.07f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerJumpThrowState::~PlayerJumpThrowState()
{
}

void PlayerJumpThrowState::Render()
{
	PlayerState::Render();
}

void PlayerJumpThrowState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if (player->GetPosition().y > player->_LegY + 68)
	{
		player->status = Player::Status::Falling;
	}
	// van toc
	if (player->GetPosition().y < player->_LegY + 68 && player->status == Player::Status::Jumping)
	{
		player->SetVy(JUMP_SPEED * 1.1);
	}
	else {
		player->SetVy(-JUMP_SPEED * 1.1);
	}
	// diem dung

	if (player->GetPosition().y < player->_LegY - 10)
	{
		player->SetState(Fall);
	}
	

	// set time cua cac frame
	if (m_Animation->GetCurrentFrameID() == 6)
		m_Animation->SetDefaultTime(0.07f);
	else m_Animation->SetDefaultTime(0.06f);


	if (m_Animation->IsLastFrame(dt) == true)
	{
		player->SetState(Fall);
	}
	// animation update
	PlayerState::Update(dt);
}

void PlayerJumpThrowState::HandleInput()
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
		player->SetVx(-RUN_SPEED / 1.1f);
		return;
	}
	player->SetVx(0);
}

void PlayerJumpThrowState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerJumpThrowState::GetStateName()
{
	return JumpThrow;
}

void PlayerJumpThrowState::ResetState(int dummy)
{
}
