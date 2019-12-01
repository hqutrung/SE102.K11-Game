#include "PlayerFallState.h"

PlayerFallState::PlayerFallState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1022, "Resources/PlayerState/fall2.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	//m_Animation->AddFrames(texs->GetTexture(1022), 1, 24, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	m_Animation->AddFramesA(texs->GetTexture(1022), 1, 1, 3, 4, 3, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
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

	//set frame ID
	
	// state trc la jump or jump cross ve frame 22 (tiep dat nhe)
	if (player->GetPosition().y <= player->_LegY - 10
		&& (player->GetPrevStateName() == Jump || player->GetPrevStateName() == JumpCross))
	{
		m_Animation->SetCurrentFrame(22);
		player->SetPosition(player->GetPosition().x, player->_LegY);
	}

	// state trc la jump or jump cross ve frame 5 (Tiep dat manh)
	if ((player->GetPosition().y <= player->_LegY - 10)
		&& (player->GetPrevStateName() == JumpAttack || player->GetPrevStateName() == JumpThrow))
	{
		m_Animation->SetCurrentFrame(5);
		player->SetPosition(player->GetPosition().x, player->_LegY);
	}

	
	// van toc
	if (m_Animation->GetCurrentFrameID() <= 4)
	{
		player->SetVy(-JUMP_SPEED);
	}
	else
	{
		player->SetVy(0);
	}

	// set time frame
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
	case 22:
		m_Animation->SetDefaultTime(0.07);
		break;
	case 23:
		m_Animation->SetDefaultTime(0.07);
		break;

	default:
		m_Animation->SetDefaultTime(0.02);
		break;
	}

	// frame cuoi -> ve state Idle
	if (m_Animation->IsLastFrame(dt) || m_Animation->GetCurrentFrameID() == 21)
	{
		player->SetState(Idle);
	}
	PlayerState::Update(dt);
}

void PlayerFallState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	if (m_Animation->GetCurrentFrameID() >= 6)
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
	// Nếu ấn right-arrow thì chạy qua phai .Neu dang cham dat -> run
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED / 1.65);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-RUN_SPEED / 1.65);
		return;
	}

	player->SetVx(0);

}

void PlayerFallState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
	auto player = playerData->player;
	auto impactorType = impactor->GetType();

	if (impactor->GetType() == Layer::StaticType )
	{
		DebugOut(L"box top= %f\n", impactor->GetRect().top);
		player->_LegY = impactor->GetRect().top;
	}

	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		//
	}

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
