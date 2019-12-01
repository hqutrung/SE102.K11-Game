#include "PlayerIdleAttackState.h"

PlayerIdleAttackState::PlayerIdleAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1002, "Resources/PlayerState/idle_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1002), 1, 10, 0.06f, D3DCOLOR_XRGB(255, 0, 255));

}

PlayerIdleAttackState::~PlayerIdleAttackState()
{
}

void PlayerIdleAttackState::Render()
{
	PlayerState::Render();
}

void PlayerIdleAttackState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));

	if (m_Animation->GetCurrentFrameID()==6)
	{
		playerData->player->SetState(Idle);
	}
	if (m_Animation->IsLastFrame(dt))
	{
		playerData->player->SetState(Idle);
	}

	PlayerState::Update(dt);
}

void PlayerIdleAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}

	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKey(RIGHT_ARROW))
	{
		countPressKey = 1;
		player->SetState(Run);
		return;
	}

}

void PlayerIdleAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
}

PlayerState::State PlayerIdleAttackState::GetStateName()
{
	return IdleAttack;
}

void PlayerIdleAttackState::ResetState()
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-18);
	player->SetColliderRight(64);
	player->SetColliderTop(44);
	player->SetColliderBottom(-24);
	PlayerState::ResetState();
}
