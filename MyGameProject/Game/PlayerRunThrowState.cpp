#include "PlayerRunThrowState.h"

PlayerRunThrowState::PlayerRunThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1168, "Resources/PlayerState/run_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1168), 1, 6, 0.07f, D3DCOLOR_XRGB(255, 0, 255));

}

void PlayerRunThrowState::Render()
{
	PlayerState::Render();
}

static bool isThrowed = false;
void PlayerRunThrowState::Update(float dt)
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

	auto posApple = playerData->player->GetPosition();
	if (playerData->player->GetMoveDirection() == Player::LeftToRight)
		posApple.x += 41;
	else
		posApple.x += -41;
	posApple.y += 33;
	if (m_Animation->GetCurrentFrameID() == 3) {
		if (!isThrowed) {
			playerData->player->ThrowApple(posApple);
			isThrowed = true;
		}
	}
	else
		isThrowed = false;
	PlayerState::Update(dt);
}

void PlayerRunThrowState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}
	if (keyboard->GetKey(ATTACK_ARROW) || keyboard->GetKeyDown(ATTACK_ARROW))
	{
		player->SetState(RunAttack);
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
	player->SetState(Run);
}

void PlayerRunThrowState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}


PlayerState::State PlayerRunThrowState::GetStateName()
{
	return RunThrow;
}

void PlayerRunThrowState::ResetState(int dummy)
{

	auto player = Player::GetInstance();
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
