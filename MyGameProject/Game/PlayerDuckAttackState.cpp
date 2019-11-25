#include "PlayerDuckAttackState.h"

PlayerDuckAttackState::PlayerDuckAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1011, "Resources/PlayerState/duck_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1011), 1, 7, 0.07f, D3DCOLOR_XRGB(255, 255, 255));

}
PlayerDuckAttackState::~PlayerDuckAttackState()
{
}

void PlayerDuckAttackState::Render()
{
	PlayerState::Render();
}

void PlayerDuckAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	player->SetVelocity(D3DXVECTOR2(0, 0));
	
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Duck);
		playerData->state->GetAnimation()->SetCurrentFrame(4);
	}

	PlayerState::Update(dt);
}

void PlayerDuckAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();


	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(DuckThrow);
			return;
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		return;
	}
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		return;
	}
	if (keyboard->GetKey(DOWN_ARROW))
		return;
}

PlayerState::State PlayerDuckAttackState::GetStateName()
{
	return DuckAttack;
}

void PlayerDuckAttackState::ResetState()
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-18);
	player->SetColliderRight(74);
	player->SetColliderTop(8);
	player->SetColliderBottom(-24);
	PlayerState::ResetState();
}
