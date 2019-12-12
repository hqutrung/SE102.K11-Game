#include "PlayerTouchGroundState.h"
#include"PlayerFallState.h"
#pragma once

PlayerTouchGroundState::PlayerTouchGroundState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1451, "Resources/PlayerState/fall2.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->GetTexture(1451), 1, 6, 3, 4, 10, 3, 10, 0.07f, D3DCOLOR_XRGB(255, 0, 255));
}

PlayerTouchGroundState::~PlayerTouchGroundState()
{
}

void PlayerTouchGroundState::Update(float dt)
{
	auto player = Player::GetInstance();
	if (player->GetState(player->GetPrevStateName())->heavy == false && m_Animation->countLoopFrame == 1)
		/*|| player->GetState(Fall)->GetAnimation()->countLoopFrame > 1)*/
	{
		m_Animation->countLoopFrame++;
		m_Animation->SetCurrentFrame(17);
	}
	//frame time
	
	if (m_Animation->GetCurrentFrameID() < 17)
	{
		m_Animation->SetDefaultTime(0.025f);
	}else m_Animation->SetDefaultTime(0.07f);
	//

	if (m_Animation->IsEndFrame(16, dt) || m_Animation->IsLastFrame(dt))
	{
		player->SetState(Idle);
	}
	PlayerState::Update(dt);
}

PlayerState::State PlayerTouchGroundState::GetStateName()
{
	return TouchGroud;
}

void PlayerTouchGroundState::ResetState(int dummy)
{
	m_Animation->countLoopFrame = 1;
	auto player = Player::GetInstance();
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
