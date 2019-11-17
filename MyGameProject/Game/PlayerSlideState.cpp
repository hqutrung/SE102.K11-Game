#include "PlayerSlideState.h"

PlayerSlideState::PlayerSlideState()
{
}

PlayerSlideState::PlayerSlideState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1012, "Resources/PlayerState/slide.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1012), 1, 9, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
}

PlayerSlideState::~PlayerSlideState()
{
}

void PlayerSlideState::Render()
{
	D3DXVECTOR3 p;
	auto player = playerData->player->GetInstance();
	if (playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
	{
		p = D3DXVECTOR3(player->GetPosition().x - (57 / 2 - 44 / 2), player->GetPosition().y + (61 / 2 - 55 / 2), 0);
		m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		p = D3DXVECTOR3(player->GetPosition().x + (57 / 2 - 44 / 2), player->GetPosition().y + (61 / 2 - 55 / 2), 0);
		m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
	}
}

void PlayerSlideState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if (player->GetMoveDirection() == Entity::MoveDirection::LeftToRight)
		player->SetVx(SLIDE_SPEED);
	else
		player->SetVx(-SLIDE_SPEED); 
	PlayerState::Update(dt);
	if (m_Animation->GetCurrentFrameID()>=4)
	{
		player->SetVx(0);
	}
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Idle);
	}
}

void PlayerSlideState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(UP_ARROW))
	{
		player->SetState(LookUp);
		return;
	}
	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(IdleAttack);
		return;
	}
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetState(Run);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetState(Run);
		return;
	}
}

PlayerState::State PlayerSlideState::GetState()
{
	return Slide;
}
