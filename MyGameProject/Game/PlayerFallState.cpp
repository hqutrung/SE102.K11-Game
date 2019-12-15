#include "PlayerFallState.h"

PlayerFallState::PlayerFallState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1022, "Resources/PlayerState/fall2.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->GetTexture(1022), 1, 1, 1, 5, 5, 3, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

PlayerFallState::~PlayerFallState()
{
}

void PlayerFallState::Render()
{
	PlayerState::Render();
}

void PlayerFallState::Update(float dt)
{
	auto player = playerData->player->GetInstance();


	player->SetVy(-JUMP_SPEED);

	//
	if (player->GetPrevStateName() == JumpAttack
		|| player->GetPrevStateName() == JumpThrow
		|| player->GetPrevStateName() == JumpCross
		|| player->GetPrevStateName() == ClimbJump
		|| m_Animation->countLoopFrame > 1)
		heavy = true;
	else heavy = false;

	//DebugOut(L"couLoopFame: %d\n", m_Animation->countLoopFrame);

	// set time frame
	switch (m_Animation->GetCurrentFrameID())
	{
	case 0:
		m_Animation->SetDefaultTime(0.2f);
		break;
	case 1:
		m_Animation->SetDefaultTime(0.08f);
		break;
	case 2:
		m_Animation->SetDefaultTime(0.08f);
		break;
	case 3:
		m_Animation->SetDefaultTime(0.08f);
		break;
	case 4:
		m_Animation->SetDefaultTime(0.2f);
		break;

	default:
		break;
	}

	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID() - 1);
		m_Animation->countLoopFrame++;
	}



	PlayerState::Update(dt);
}

void PlayerFallState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKey(THROW_ARROW))
	{
		player->SetState(JumpThrow);
		return;
	}
	if (keyboard->GetKey(ATTACK_ARROW))
	{
		player->SetState(JumpAttack);
		return;
	}
	// Nếu ấn right-arrow thì chạy qua phai
	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-RUN_SPEED);
		return;
	}

	player->SetVx(0);

}

void PlayerFallState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = playerData->player;
	if (player->status == Player::Status::OnGround
		&& (impactor->GetTag() == GROUND || (impactor->GetTag() == STONE && impactor->IsCollidable())) && player->GetCurrentState()->GetStateName() != TouchGroud)
	{
		player->SetState(TouchGroud);
	}
}

PlayerState::State PlayerFallState::GetStateName()
{
	return Fall;
}

void PlayerFallState::ResetState(int dummy)
{
	m_Animation->countLoopFrame = 1;
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
