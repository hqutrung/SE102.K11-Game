#include "PlayerRunAttackState.h"

PlayerRunAttackState::PlayerRunAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1003, "Resources/PlayerState/run_attack_after.png", D3DCOLOR_XRGB(255,0,255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1003), 1, 6, 0.08, D3DCOLOR_XRGB(255,0,255));

}

void PlayerRunAttackState::Render()
{
	PlayerState::Render();
}

void PlayerRunAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();

	if (player->GetMoveDirection() == Entity::MoveDirection::LeftToRight)
	{
		player->SetVx(RUN_SPEED);
	}
	else {
		if (player->GetMoveDirection() == Entity::MoveDirection::RightToLeft)
		{
			player->SetVx(-RUN_SPEED);
		}
	}

	//set default time
	auto frameID = m_Animation->GetCurrentFrameID();
	switch (frameID)
	{
	case 0:
		Sound::GetInstance()->PlayFX(ALADDIN_IDLE_SPLASH);
	case 1:
	case 2:
		m_Animation->SetDefaultTime(0.03f);
		break;
	default:
		m_Animation->SetDefaultTime(0.07f);
		break;
	}
	
	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Run);
	}

	PlayerState::Update(dt);


	//isAttack
	if (Support::IsContainedIn(m_Animation->GetCurrentFrameID(), 3, 5))
		playerData->player->isAttack = true;
	else playerData->player->isAttack = false;

}

void PlayerRunAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}
	if ((keyboard->GetKey(THROW_ARROW) || keyboard->GetKeyDown(THROW_ARROW)) && player->GetApples() > 0)
	{
		player->SetState(RunThrow);
		return;
	}
	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		return;
	}
	player->SetState(Run);
}

void PlayerRunAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	if (impactor->GetTag() == JAFAR)
	{
		Player::GetInstance()->SetState(Somersault);
	}
}

PlayerState::State PlayerRunAttackState::GetStateName()
{
	return RunAttack;
}

void PlayerRunAttackState::ResetState(int dummy)
{
	auto player = Player::GetInstance();
	player->SetColliderLeft(-10);
	player->SetColliderRight(62);
	player->SetColliderTop(40);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
