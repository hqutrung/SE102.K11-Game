#include "PlayerDuckState.h"

PlayerDuckState::PlayerDuckState(PlayerData* data)
{

	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1010, "Resources/PlayerState/duck_after.png", D3DCOLOR_XRGB(255,0,255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1010), 1, 5, 0.08f, D3DCOLOR_XRGB(255,0,255));

}

PlayerDuckState::~PlayerDuckState()
{
}

void PlayerDuckState::Render()
{
	PlayerState::Render();

}

void PlayerDuckState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID() - 1);
	}
	PlayerState::Update(dt);
}

void PlayerDuckState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	//duck->jump
	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(Jump);
		return;
	}

	if (keyboard->GetKeyDown(THROW_ARROW))
	{
		player->SetState(DuckThrow);
		return;
	}

	//duck->duckAttack
	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		player->SetState(DuckAttack);
	}
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetVx(0.000000000000000000000001);
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-0.000000000000000000000001);
	}

	if (keyboard->GetKey(DOWN_ARROW) || keyboard->GetKeyDown(DOWN_ARROW))
	{
		return;
	}
	//duck->idle
	player->SetState(Idle);
}

PlayerState::State PlayerDuckState::GetStateName()
{
	return Duck;
}
