#include "PlayerLookUpState.h"

PlayerLookUpState::PlayerLookUpState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1014, "Resources/PlayerState/look_up_after.png", D3DCOLOR_XRGB(255,0,255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1014), 1, 4, 0.08f, D3DCOLOR_XRGB(255, 0, 255));

}

PlayerLookUpState::~PlayerLookUpState()
{
}

void PlayerLookUpState::Render()
{
	PlayerState::Render();
}

void PlayerLookUpState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->countLoopFrame++;
		return;
	}
	PlayerState::Update(dt);
}

void PlayerLookUpState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	
	if (keyboard->GetKey(THROW_ARROW) && player->GetApples() > 0)
	{
		player->SetState(IdleThrow);
		return;
	}

	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(Jump);
		return;
	}

	if (keyboard->GetKeyDown(ATTACK_ARROW)&& player->GetState(LookUpAttack)->countPressKey==1)
	{
		player->SetState(LookUpAttack);
		return;
	}

	if (keyboard->GetKey(RIGHT_ARROW))
	{
		player->SetVx(0.000000000000000000000001);
	}
	if (keyboard->GetKey(LEFT_ARROW))
	{
		player->SetVx(-0.000000000000000000000001);
	}


	if (keyboard->GetKey(UP_ARROW))
	{
		return;
	}
	player->SetState(Idle);
}

void PlayerLookUpState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerLookUpState::GetStateName()
{
	return LookUp;
}

void PlayerLookUpState::ResetState(int dummy)
{
	auto player = playerData->player;

	//collider around center point, collider often smaller than player sprite

	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);

	if (player->GetPrevStateName() == IdleThrow)
		m_Animation->SetCurrentFrame(3);
	else PlayerState::ResetState(dummy);
}
