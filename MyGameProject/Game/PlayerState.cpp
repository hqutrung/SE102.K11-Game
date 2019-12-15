#include "PlayerState.h"
#include "Player.h"

PlayerState::~PlayerState()
{
}

void PlayerState::Update(float dt)
{
	m_Animation->Update(dt);
}

void PlayerState::Render()
{
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void PlayerState::HandleInput()
{
}

PlayerState::State PlayerState::GetStateName()
{
	return Idle;
}

void PlayerState::ResetState(int dummy)
{
	m_Animation->ResetAnimation();
}

BoxCollider PlayerState::GetBody()
{
	return playerData->player->GetBigBound();
}

void PlayerState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::PlayerState(PlayerData* data)
{
	this->playerData = data;
}

PlayerState::PlayerState()
{
}
