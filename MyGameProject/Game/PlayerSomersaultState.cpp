#include "PlayerSomersaultState.h"

PlayerSomersaultState::PlayerSomersaultState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(10011, "Resources/PlayerState/somersault.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(10011), 1, 8, 0.08f, D3DCOLOR_XRGB(255, 255, 255));
	heavy = true;
}

PlayerSomersaultState::~PlayerSomersaultState()
{
}

void PlayerSomersaultState::Render()
{
	PlayerState::Render();
}

void PlayerSomersaultState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if (player->status == Player::Status::Jumping)
		player->SetVy(JUMP_SPEED);
	if (player->GetPosition().y >= player->lastposition.y + MAX_JUMP - 5)
	{
		player->status = Player::Status::Falling;
		player->SetVy(-JUMP_SPEED);
	}

	if (player->status == Player::Jumping)
	{
		if (player->GetMoveDirection() == Entity::LeftToRight)
		{
			player->SetVx(-RUN_SPEED * 1.2f);
			player->SetMoveDirection(Player::LeftToRight);
		}
		else {
			player->SetVx(RUN_SPEED * 1.2f);
			player->SetMoveDirection(Player::RightToLeft);
		}
	}
	if (m_Animation->IsLastFrame(dt) && player->status != Player::Status::OnGround)
		player->SetState(Fall);
	PlayerState::Update(dt);

}

void PlayerSomersaultState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(JUMP_ARROW))
	{
		countPressKey++;
	}


	// Nếu ấn right-arrow thì chạy qua phai
	if (player->status == Player::Falling)
	{
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
		if (keyboard->GetKey(RIGHT_ARROW))
		{
			player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
			player->SetVx(RUN_SPEED * 0.5f);
			return;
		}
		// Nếu ấn left-arrow thì chạy qua trái
		if (keyboard->GetKey(LEFT_ARROW))
		{
			player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
			player->SetVx(-RUN_SPEED * 0.5f);
			return;
		}
		player->SetVx(0);
	}
}

void PlayerSomersaultState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = playerData->player;
	if (player->status == Player::Status::OnGround
		&& (impactor->GetTag() == GROUND || (impactor->GetTag() == STONE && impactor->IsCollidable())) && player->GetPrevStateName() != TouchGroud)
	{
		player->SetState(TouchGroud);
	}
}

PlayerState::State PlayerSomersaultState::GetStateName()
{
	return Somersault;
}

void PlayerSomersaultState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
