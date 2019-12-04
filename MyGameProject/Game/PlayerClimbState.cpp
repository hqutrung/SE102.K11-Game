#include "PlayerClimbState.h"

PlayerClimbState::PlayerClimbState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1245, "Resources/PlayerState/climb_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1245), 2, 8, 0.05f, D3DCOLOR_XRGB(255, 0, 255));

}

PlayerClimbState::~PlayerClimbState()
{

}

void PlayerClimbState::Render()
{
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

}

void PlayerClimbState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	player->SetVelocity(D3DXVECTOR2(0, 0));

	if (keyboard->GetKey(UP_ARROW))
	{
		if (m_Animation->countLoopFrame == 1)
			m_Animation->Update(dt);
		player->SetVy(CLIMB_SPEED);
	}
	else if (keyboard->GetKey(DOWN_ARROW))
	{
		player->SetVy(-CLIMB_SPEED);
		m_Animation->Update1(dt);
	}

	switch (m_Animation->GetCurrentFrameID())
	{
	case 1:
	case 9:
		m_Animation->SetDefaultTime(0.03f);

	default:
		m_Animation->SetDefaultTime(0.05f);
		break;
	}

}

void PlayerClimbState::HandleInput()
{

	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKey(DIK_I))
	{
		player->SetState(Idle);
		return;
	}

	if (keyboard->GetKey(ATTACK_ARROW) && player->GetState(ClimbAttack)->countPressKey == 1)
	{
		player->SetState(ClimbAttack);
		return;
	}
	if (keyboard->GetKey(THROW_ARROW) && player->GetState(ClimbThrow)->countPressKey == 1)
	{
		player->SetState(ClimbThrow);
		return;
	}

	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-0.00000000001);
		return;
	}
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetVx(0.00000000001);
		return;
	}
	//if (keyboard->GetKey(JUMP_ARROW))
	//{
	//	player->SetState(ClimbJump);
	//	return;
	//}



}

void PlayerClimbState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = Player::GetInstance();

	if (player->status == Player::Status::Climbing
		&& impactor->GetTag() == CHAINE
		&& player->GetRect().bottom < impactor->GetRect().bottom)
	{
		player->SetState(PlayerState::Fall);
	}
	if (player->status == Player::Status::Climbing
		&& impactor->GetTag() == CHAINE
		&& player->GetPosition().y > impactor->GetRect().top - 87 && player->GetVy() > 0)
	{
		m_Animation->countLoopFrame++;
		player->SetVy(0);
	}
	else m_Animation->countLoopFrame = 1;
}

PlayerState::State PlayerClimbState::GetStateName()
{
	return Climb;
}

void PlayerClimbState::ResetState(int dummy)
{
	/*PlayerState::ResetState(dummy);*/
}
