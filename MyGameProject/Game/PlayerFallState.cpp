#include "PlayerFallState.h"

PlayerFallState::PlayerFallState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1022, "Resources/PlayerState/fall_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1022), 1, 7, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
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


	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.1f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.08f);
		break;
	case 3:
		m_Animation->SetDefaultTime(0.06f);
		break;
	case 4:
		m_Animation->SetDefaultTime(1.0f);
		break; 
	case 5:
		m_Animation->SetDefaultTime(0.07);
		break;
	case 6:
		m_Animation->SetDefaultTime(0.07);
		break;

	default:
		m_Animation->SetDefaultTime(0.1);
		break;
	}

	// Diem dung tam thoi

	if (player->GetPosition().y <= player->_LegY-10)
	{
		m_Animation->SetCurrentFrame(5);
		player->SetPosition(player->GetPosition().x, player->_LegY);
		player->SetVy(0);
	}
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Idle);
	}
	PlayerState::Update(dt);
}

void PlayerFallState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();


	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED / 1.65);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetVx(- RUN_SPEED / 1.65);
		return;
	}

	player->SetVx(0);

}

PlayerState::State PlayerFallState::GetStateName()
{
	return Fall;
}

void PlayerFallState::ResetState()
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(9);
	player->SetColliderBottom(-22);
	PlayerState::ResetState();
}
