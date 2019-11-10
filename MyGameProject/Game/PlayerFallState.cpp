#include "PlayerFallState.h"

PlayerFallState::PlayerFallState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1022, "Resources/PlayerState/aladinfalling.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1022), 1, 4, 0.2f, D3DCOLOR_XRGB(255, 255, 255));
}

PlayerFallState::~PlayerFallState()
{
}

void PlayerFallState::Render()
{
	PlayerState::Render();
}

void PlayerFallState::Update(float dt)
{
	auto player = playerData->player->GetInstance();

	player->SetVy(-JUMP_SPEED);

	if (m_Animation->IsLastFrame(dt) == true)
	{
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID() - 1);
	}	

	// colision tam
	if (player->GetPosition().y <= player->GetPre_Y_Position())
		player->SetState(Idle);
	//    ====

	PlayerState::Update(dt);
}

void PlayerFallState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();


	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetVx(-RUN_SPEED);
		return;
	}
}
