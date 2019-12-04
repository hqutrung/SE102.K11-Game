#include "PlayerClimbAttackState.h"

PlayerClimbAttackState::PlayerClimbAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1248, "Resources/PlayerState/climb_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1248), 1, 8, 0.06f, D3DCOLOR_XRGB(255, 0, 255));

}

PlayerClimbAttackState::~PlayerClimbAttackState()
{
}

void PlayerClimbAttackState::Render()
{
	PlayerState::Render();
}

void PlayerClimbAttackState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));

	
	if (m_Animation->IsLastFrame(dt))
	{
		playerData->player->SetState(Climb);
	}

	PlayerState::Update(dt);
}

void PlayerClimbAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(ClimbThrow);
		return;
	}

	if (keyboard->GetKeyDown(UP_ARROW)|| keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Climb);
		return;
	}

	if (keyboard->GetKeyDown(ATTACK_ARROW) || keyboard->GetKey(ATTACK_ARROW))
	{
		countPressKey++;
	}


}

void PlayerClimbAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerClimbAttackState::GetStateName()
{
	return ClimbAttack;
}

void PlayerClimbAttackState::ResetState(int dummy)
{
	PlayerState::ResetState(dummy);
}
