#include "PlayerDeathState.h"

PlayerDeathState::PlayerDeathState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1271, "Resources/PlayerState/death_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->GetTexture(1271), 1,1, 3,8,10, 3,10,0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

void PlayerDeathState::Render()
{
	PlayerState::Render();
}

void PlayerDeathState::Update(float dt)
{
	auto player = Player::GetInstance();
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetPosition(100, 65);
		player->SetState(Idle);
	}
	PlayerState::Update(dt);
}

void PlayerDeathState::HandleInput()
{
}

void PlayerDeathState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerDeathState::GetStateName()
{
	return Death;
}

void PlayerDeathState::ResetState(int dummy)
{
	PlayerState::ResetState(dummy);
}
