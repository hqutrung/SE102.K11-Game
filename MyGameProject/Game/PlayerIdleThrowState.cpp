#include "PlayerIdleThrowState.h"
//aaaaa
PlayerIdleThrowState::PlayerIdleThrowState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1030, "Resources/PlayerState/idle_throw_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1030), 1, 8, 0.05f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerIdleThrowState::~PlayerIdleThrowState()
{
}

void PlayerIdleThrowState::Render()
{
	PlayerState::Render();

}

void PlayerIdleThrowState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		if(playerData->player->GetPrevStateName()==LookUp)
			playerData->player->SetState(LookUp);
		else
			playerData->player->SetState(Idle);
	}

	PlayerState::Update(dt);
}

void PlayerIdleThrowState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	
	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(IdleAttack);
		return;
	}
	if (keyboard->GetKeyDown(THROW_ARROW))
	{
		countPressKey++;
		return;
	}

	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetState(Run);
		return;
	}

}

void PlayerIdleThrowState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerIdleThrowState::GetStateName()
{
	return IdleThrow;
}

void PlayerIdleThrowState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-20);
	player->SetColliderRight(34);
	player->SetColliderTop(38);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
