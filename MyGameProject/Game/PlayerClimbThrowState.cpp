#include "PlayerClimbThrowState.h"

PlayerClimbThrowState::PlayerClimbThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1256, "Resources/PlayerState/climb_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1256), 1, 6, 0.06f, D3DCOLOR_XRGB(255, 0, 255));

}

void PlayerClimbThrowState::Render()
{
	PlayerState::Render();
}

static bool isThrowed = false;
void PlayerClimbThrowState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));


	if (m_Animation->IsLastFrame(dt))
	{
		playerData->player->SetState(Climb);
	}

	auto posApple = playerData->player->GetPosition();
	if (playerData->player->GetMoveDirection() == Player::LeftToRight)
		posApple.x += 30;
	else
		posApple.x += -30;
	posApple.y += 9;
	if (m_Animation->GetCurrentFrameID() == 4) {
		if (!isThrowed) {
			playerData->player->ThrowApple(posApple);
			isThrowed = true;
		}
	}
	else
		isThrowed = false;
	PlayerState::Update(dt);
}

void PlayerClimbThrowState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(ClimbAttack);
		return;
	}

	if (keyboard->GetKeyDown(UP_ARROW) || keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Climb);
		return;
	}
	if (keyboard->GetKeyDown(THROW_ARROW) || keyboard->GetKey(THROW_ARROW))
	{
		countPressKey++;
	}
}

void PlayerClimbThrowState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerClimbThrowState::GetStateName()
{
	return ClimbThrow;
}

void PlayerClimbThrowState::ResetState(int dummy)
{
	auto player = Player::GetInstance();
	player->SetColliderLeft(-15);
	player->SetColliderRight(15);
	player->SetColliderTop(37);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}

BoxCollider PlayerClimbThrowState::GetBody()
{
	auto pos = Player::GetInstance()->GetPosition();
	return BoxCollider(pos.y + 37, pos.x - 6, pos.x + 6, pos.y - 24);
}
