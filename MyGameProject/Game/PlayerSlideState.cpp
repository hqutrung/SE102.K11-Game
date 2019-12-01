#include "PlayerSlideState.h"

PlayerSlideState::PlayerSlideState()
{
}

PlayerSlideState::PlayerSlideState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1012, "Resources/PlayerState/slide_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1012), 1, 12, 0.08f, D3DCOLOR_XRGB(255, 255, 255));
}

PlayerSlideState::~PlayerSlideState()
{
}

void PlayerSlideState::Render()
{
	PlayerState::Render();
}

void PlayerSlideState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	if (player->GetMoveDirection() == Entity::MoveDirection::LeftToRight)
		player->SetVx(SLIDE_SPEED);
	else
		player->SetVx(-SLIDE_SPEED); 
	
	if (m_Animation->GetCurrentFrameID()>=4)
	{
		player->SetVx(0);
	}
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Idle);
	}

	PlayerState::Update(dt);
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
	if (keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Duck);
		return;
	}
	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(IdleAttack);
		return;
	}
	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(IdleThrow);
		return;
	}
	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(Jump);
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
		player->SetState(Run);
		return;
	}
}

void PlayerSlideState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
}

PlayerState::State PlayerSlideState::GetStateName()
{
	return Slide;
}

void PlayerSlideState::ResetState(int dummy)
{
}
