#include "PlayerPushState.h"

PlayerPushState::PlayerPushState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1278, "Resources/PlayerState/push_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(Textures::GetInstance()->GetTexture(1278), 1, 9, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

void PlayerPushState::Render()
{
	PlayerState::Render();
}


void PlayerPushState::Update(float dt)
{

	auto player = Player::GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	if (m_Animation->GetCurrentFrameID() == 0);
		Sound::GetInstance()->PlayFX(ALADDIN_PUSH);
	if (m_Animation->IsLastFrame(dt) == true)
	{
		m_Animation->countLoopFrame++;
		m_Animation->SetCurrentFrame(1);
	}

	if ((keyboard->GetKey(RIGHT_ARROW) && player->GetMoveDirection() == Player::MoveDirection::LeftToRight)
		|| (keyboard->GetKey(LEFT_ARROW) && player->GetMoveDirection() == Player::MoveDirection::RightToLeft))
	{
		player->SetVx(0);
		m_Animation->Update(dt);
	}
	else
		player->SetState(Idle);
}

void PlayerPushState::HandleInput()
{

}

void PlayerPushState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	if (impactor->GetTag()== JAFARWEAPON)
	{
		Player::GetInstance()->SetState(Idle);
	}
}

PlayerState::State PlayerPushState::GetStateName()
{
	return Push;
}

void PlayerPushState::ResetState(int dummy)
{
	auto player = playerData->player;
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
