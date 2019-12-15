#include "PlayerIdleAttackState.h"

PlayerIdleAttackState::PlayerIdleAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1002, "Resources/PlayerState/idle_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1002), 1, 9, 0.06f, D3DCOLOR_XRGB(255, 0, 255));

}

PlayerIdleAttackState::~PlayerIdleAttackState()
{
}

void PlayerIdleAttackState::Render()
{
	PlayerState::Render();
}

void PlayerIdleAttackState::Update(float dt)
{

	auto player = Player::GetInstance();
	player->SetVelocity(D3DXVECTOR2(0, 0));


	//set default time
	auto frameID = m_Animation->GetCurrentFrameID();
	switch (frameID)
	{
	case 0:
	case 1:
		m_Animation->SetDefaultTime(0.02f);
		break;
	case 2:
	case 3:
	case 4:
		m_Animation->SetDefaultTime(0.04f);
		break;
	default:
		m_Animation->SetDefaultTime(0.06f);
		break;
	}

	// chuyen state
	if (m_Animation->IsEndFrame(5, dt))
	{
		m_Animation->countLoopFrame = 1;
		playerData->player->SetState(Idle);
	}
	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->countLoopFrame = 1;
		playerData->player->SetState(Idle);
	}



	PlayerState::Update(dt);


	// isAttack
	if (Support::IsContainedIn(m_Animation->GetCurrentFrameID(), 2, 4))
	{
		player->isAttack = true;
	}
	else player->isAttack = false;

}

void PlayerIdleAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(THROW_ARROW) && player->GetApples() > 0)
	{
		player->SetState(IdleThrow);
		return;
	}
	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}

	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKey(RIGHT_ARROW))
	{
		countPressKey = 1;
		player->SetState(Run);
		return;
	}

}

void PlayerIdleAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	if (impactor->GetTag() == WALL && m_Animation->countLoopFrame == 1 && m_Animation->IsEndFrame(2, dt))
	{
		m_Animation->SetCurrentFrame(6);
		Player::GetInstance()->isAttack = false;
		m_Animation->countLoopFrame++;
	}
}

PlayerState::State PlayerIdleAttackState::GetStateName()
{
	return IdleAttack;
}

void PlayerIdleAttackState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(62);
	player->SetColliderTop(40);
	player->SetColliderBottom(-25);
	PlayerState::ResetState(dummy);
}
