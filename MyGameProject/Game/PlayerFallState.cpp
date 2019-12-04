#include "PlayerFallState.h"

PlayerFallState::PlayerFallState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1022, "Resources/PlayerState/fall2.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	//m_Animation->AddFrames(texs->GetTexture(1022), 1, 24, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	m_Animation->AddFramesA(texs->GetTexture(1022), 1, 1, 3, 4,10, 3, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
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
	// set time frame
	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 3:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 4:
		m_Animation->SetDefaultTime(100.0f);
		break;
	case 22:
		m_Animation->SetDefaultTime(0.05);
		break;
	case 23:
		m_Animation->SetDefaultTime(0.05);
		break;

	default:
		m_Animation->SetDefaultTime(0.02);
		break;
	}

	// frame cuoi -> ve state Idle
	if (m_Animation->IsLastFrame(dt) || m_Animation->GetCurrentFrameID() == 21 )
	{
		m_Animation->countLoopFrame = 1;
	}
	PlayerState::Update(dt);
}

void PlayerFallState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	/*if (m_Animation->GetCurrentFrameID() >= 6)
	{
		if (keyboard->GetKey(JUMP_ARROW) || keyboard->GetKeyDown(JUMP_ARROW))
		{
			player->SetState(Jump);
			return;
		}
		if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW) || keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
		{
			player->SetState(Run);
			return;
		}
	}
	if (keyboard->GetKey(JUMP_ARROW)&&m_Animation->GetCurrentFrameID()>=5&&player->GetState(Jump)->countPressKey==1)
	{
		player->SetState(Jump);
		return;
	}*/

	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED *0.8);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-RUN_SPEED *0.8);
		return;
	}

	player->SetVx(0);

}

void PlayerFallState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	
}

PlayerState::State PlayerFallState::GetStateName()
{
	return Fall;
}

void PlayerFallState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
