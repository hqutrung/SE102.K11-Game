#include "PlayerJumpState.h"

PlayerJumpState::PlayerJumpState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1021, "Resources/PlayerState/jump_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1021), 1, 4, 0.1f, D3DCOLOR_XRGB(255, 255, 255));

}

void PlayerJumpState::Render()
{
	PlayerState::Render();
}

void PlayerJumpState::Update(float dt)
{

	auto player = playerData->player->GetInstance();
	player->SetVy(JUMP_SPEED);
	if (player->GetPosition().y >= player->lastposition.y + MAX_JUMP)
	{
		player->status == Player::Status::Falling;
		player->SetState(Fall);
		player->SetVy(-JUMP_SPEED);
	}

	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.05f);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.075f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.1f);
		break;
	case 3:
		m_Animation->SetDefaultTime(0.4f);
		break;

	default:
		m_Animation->SetDefaultTime(0.2f);
		break;
	}
	PlayerState::Update(dt);
	

}

void PlayerJumpState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(THROW_ARROW) && player->GetApples() > 0)
	{
		player->SetState(JumpThrow);
		return;
	}
	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(JumpAttack);
		return;
	}

	if (keyboard->GetKey(JUMP_ARROW)|| keyboard->GetKeyDown(JUMP_ARROW))
	{
		countPressKey++;
	}
	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-RUN_SPEED);
		return;
	}
	player->SetVx(0);
}

void PlayerJumpState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{

}

PlayerState::State PlayerJumpState::GetStateName()
{
	return Jump;
}

void PlayerJumpState::ResetState(int dummy)
{
	auto player = Player::GetInstance();

	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
