#include "PlayerJumpState.h"

PlayerJumpState::PlayerJumpState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1021, "Resources/PlayerState/jump_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1021), 1, 4, 0.1f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Render()
{
	PlayerState::Render();
}

void PlayerJumpState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if (player->GetPosition().y > player->_LegY + 75)
	{
		player->status = Player::Status::Jumping;
	}
	
	if (player->GetPosition().y < player->_LegY + 75 && player->status == Player::Status::Jumping)
	{
		player->SetVy(JUMP_SPEED);
		DebugOut(L"y= %f\n", player->GetPosition().y);
	}
	else {
		player->SetVy(-JUMP_SPEED);
		player->SetState(Fall);
		DebugOut(L"y= %f\n", player->GetPosition().y);
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

	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(JumpThrow);
	}
	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(JumpAttack);
	}
	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetVx(RUN_SPEED/1.5);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetVx(-RUN_SPEED/1.5);
		return;
	}
	player->SetVx(0);
}

void PlayerJumpState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
	auto player = playerData->player;
	auto impactorType = impactor->GetType();
	
	if (impactorType == Layer::ItemAvailableType ) {
		impactor->SetActive(false);
		player->_LegY = 40;
		//DebugOut(L"Va cham");

	}
	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		//
	}
}

PlayerState::State PlayerJumpState::GetStateName()
{
	return Jump;
}

void PlayerJumpState::ResetState(int dummy)
{
	auto player = Player::GetInstance();

	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(0);
	player->SetColliderTop(0);
	player->SetColliderBottom(0);
	player->SetColliderRight(0);

	PlayerState::ResetState(dummy);
}
