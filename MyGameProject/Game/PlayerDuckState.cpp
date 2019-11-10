#include "PlayerDuckState.h"

PlayerDuckState::PlayerDuckState(PlayerData* data)
{

	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1010, "Resources/PlayerState/aladinduck.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1010), 1, 4, 0.1f, D3DCOLOR_XRGB(255, 255, 255));

}

PlayerDuckState::~PlayerDuckState()
{
}

void PlayerDuckState::Render()
{
	auto player = playerData->player->GetInstance();

	D3DXVECTOR3 p;
	p = D3DXVECTOR3(player->GetPosition().x , player->GetPosition().y - (55 / 2 - 49 / 2), 0);

	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

}

void PlayerDuckState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID()- 1);
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

	//duck->duckAttack
	if (keyboard->GetKey(ATTACK_ARROW))
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
