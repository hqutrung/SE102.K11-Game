#include "PlayerClimbJumpState.h"

PlayerClimbJumpState::PlayerClimbJumpState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1264, "Resources/PlayerState/climb_jump_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1264), 1, 9, 0.08f, D3DCOLOR_XRGB(255, 255, 255));
	
}

void PlayerClimbJumpState::Render()
{
	PlayerState::Render();
}

void PlayerClimbJumpState::Update(float dt)
{
	auto player = Player::GetInstance();

	if (player->GetPosition().y >  player->lastposition.y + MAX_JUMP)
	{
		player->status = Player::Status::Falling;
	}

	if (player->status == Player::Status::Jumping)
	{
		player->SetVy(JUMP_SPEED);
	}
	else if (player->status ==Player::Status::Falling)
	{
		player->SetVy(-JUMP_SPEED);
	}


	// set frame time
	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.08f);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.2f);
		break;
	default:
		m_Animation->SetDefaultTime(0.08f);
		break;
	}

	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Fall);
	}
	PlayerState::Update(dt);
}

void PlayerClimbJumpState::HandleInput()
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

	if (keyboard->GetKey(JUMP_ARROW) || keyboard->GetKeyDown(JUMP_ARROW))
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

void PlayerClimbJumpState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = playerData->player;
	if (player->status == Player::Status::OnGround
		&& (impactor->GetTag() == GROUND || (impactor->GetTag() == STONE && impactor->IsCollidable())) && player->GetPrevStateName() != TouchGroud)
	{
		player->SetState(TouchGroud);
	}
}

PlayerState::State PlayerClimbJumpState::GetStateName()
{
	return ClimbJump;
}

void PlayerClimbJumpState::ResetState(int dummy)
{
	auto player = Player::GetInstance();
	player->SetColliderLeft(-15);
	player->SetColliderRight(15);
	player->SetColliderTop(37);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
