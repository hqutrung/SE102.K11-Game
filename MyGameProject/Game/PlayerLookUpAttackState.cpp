#include "PlayerLookUpAttackState.h"

PlayerLookUpAttackState::PlayerLookUpAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1020, "Resources/PlayerState/look_up_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1020), 1, 12, 0.1f, D3DCOLOR_XRGB(255, 0, 255));

}

void PlayerLookUpAttackState::Render()
{
	PlayerState::Render();
}

void PlayerLookUpAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	player->SetVelocity(D3DXVECTOR2(0, 0));


	if (m_Animation->countLoopFrame >= 3 && m_Animation->GetCurrentFrameID() == 4)
		m_Animation->SetCurrentFrame(10);

	if (m_Animation->GetCurrentFrameID() == 9)
	{
		m_Animation->countLoopFrame++;
		playerData->state->GetAnimation()->SetCurrentFrame(2);
	}

	if (m_Animation->IsLastFrame(dt))
	{
		player->SetState(Idle);
		m_Animation->countLoopFrame = 1;
	}

	int id = m_Animation->GetCurrentFrameID();
	switch (id)
	{
	case 2:
	case 6:
	//case 9:
		Sound::GetInstance()->PlayFX(ALADDIN_IDLE_SPLASH);
		break;
	default:
		break;
	}
	PlayerState::Update(dt);

	//isAttack
	if (Support::IsContainedIn(m_Animation->GetCurrentFrameID(), 2, 3) || Support::IsContainedIn(m_Animation->GetCurrentFrameID(), 6, 7))
		playerData->player->isAttack = true;
	else playerData->player->isAttack = false;

}

void PlayerLookUpAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(DOWN_ARROW))
	{
		player->SetState(Duck);
		return;
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::RightToLeft);
		player->SetState(Run);
		return;
	}
	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetMoveDirection(Entity::MoveDirection::LeftToRight);
		player->SetState(Run);
		return;
	}
	if (keyboard->GetKeyDown(ATTACK_ARROW))
	{
		countPressKey++;
		return;
	}
	if (keyboard->GetKey(UP_ARROW))
	{
		return;
	}
}

void PlayerLookUpAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerLookUpAttackState::GetStateName()
{
	return LookUpAttack;
}

void PlayerLookUpAttackState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-45);
	player->SetColliderRight(52);
	player->SetColliderTop(40);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
