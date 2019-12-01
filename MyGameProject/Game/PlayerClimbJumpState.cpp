#include "PlayerClimbJumpState.h"

PlayerClimbJumpState::PlayerClimbJumpState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1264, "Resources/PlayerState/climb_jump_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1264), 1, 9, 0.08f, D3DCOLOR_XRGB(255, 255, 255));

}

void PlayerClimbJumpState::Render()
{
	PlayerState::Render();
}

void PlayerClimbJumpState::Update(float dt)
{

}

void PlayerClimbJumpState::HandleInput()
{
}

PlayerState::State PlayerClimbJumpState::GetStateName()
{
	return ClimbJump;
}

void PlayerClimbJumpState::ResetState()
{
	PlayerState::ResetState();
}
