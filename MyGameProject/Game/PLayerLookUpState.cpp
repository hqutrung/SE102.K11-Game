#include "PLayerLookUpState.h"

PlayerLookUpState::PlayerLookUpState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1014, "Resources/PlayerState/lookup.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1014), 1, 3, 0.1f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerLookUpState::~PlayerLookUpState()
{
}

void PlayerLookUpState::Render()
{
	PlayerState::Render();
}

void PlayerLookUpState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID() - 1);
	}
	PlayerState::Update(dt);
}

void PlayerLookUpState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	
	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(Jump);
		return;
	}

	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(LookUpAttack);
		return;
	}

	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetVx(0.000000000000000000000001);
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-0.000000000000000000000001);
	}


	if (keyboard->GetKey(UP_ARROW))
	{
		return;
	}
	player->SetState(Idle);
}
