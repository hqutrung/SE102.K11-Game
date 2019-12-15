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
	m_Animation->AddFrames(texs->GetTexture(1012), 1, 12, 0.06f, D3DCOLOR_XRGB(255, 255, 255));
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
	// test
	if (keyboard->GetKey(DIK_L))
	{
		player->SetState(Death);
		return;
	}
	if (keyboard->GetKey(DIK_J))
	{
		player->SetState(Climb);
		return;
	}

	if (keyboard->GetKey(DIK_K))
	{
		player->SetState(Injured);
		return;
	}
	//=====================

	if (keyboard->GetKeyDown(THROW_ARROW) && player->GetState(IdleThrow)->countPressKey == 1)
	{
		player->SetState(IdleThrow);
		return;
	}

	if (keyboard->GetKeyDown(JUMP_ARROW) && player->GetState(Jump)->countPressKey == 1)
	{
		player->SetState(Jump);
		return;
	}

	if (keyboard->GetKey(UP_ARROW))
	{
		player->SetState(LookUp);
		return;
	}

	// Nếu nhấn down-arrow thì duck
	if (keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Duck);
		return;
	}



	//====idle->idle_attack

	if (keyboard->GetKeyDown(ATTACK_ARROW) && player->GetState(IdleAttack)->countPressKey == 1)
	{
		player->SetState(IdleAttack);
		return;
	}

	//=== idle->run 

	if (keyboard->GetKey(LEFT_ARROW) && keyboard->GetKey(RIGHT_ARROW))
	{
		return;
	}
	// Nếu ấn right-arrow thì chạy qua phải

	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetState(Run);
		player->SetVy(0);
		return;
	}

	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetState(Run);
		player->SetVy(0);
		return;
	}
}

void PlayerSlideState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerSlideState::GetStateName()
{
	return Slide;
}

void PlayerSlideState::ResetState(int dummy)
{

	auto player = Player::GetInstance();
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
