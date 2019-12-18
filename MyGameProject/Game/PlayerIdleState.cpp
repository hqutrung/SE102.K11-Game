#include "PlayerIdleState.h"

PlayerIdleState::PlayerIdleState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1000, "Resources/PlayerState/idle_after.png", D3DCOLOR_XRGB(255, 0, 255));

	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->GetTexture(1000), 1, 1, 5, 7, 10, 5, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));

}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Render()
{
	auto player = playerData->player->GetInstance();
	D3DXVECTOR3	p = D3DXVECTOR3(player->GetPosition().x, player->GetPosition().y + 1, 0);
	m_Animation->Render(p, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void PlayerIdleState::Update(float dt)
{

	auto player = playerData->player->GetInstance();

	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->GetCurrentFrameID() == 0 || m_Animation->GetCurrentFrameID() == 3 || m_Animation->GetCurrentFrameID() == 7)
		m_Animation->SetDefaultTime(0.8f);
	else
		m_Animation->SetDefaultTime(0.10f);

	if (m_Animation->IsLastFrame(dt) == true)
	{
		m_Animation->SetCurrentFrame(15);
	}

	PlayerState::Update(dt);
}


void PlayerIdleState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	// test
	if (keyboard->GetKey(DIK_J))
	{
		player->SetState(Climb);
		return;
	}


	if (keyboard->GetKeyDown(THROW_ARROW) && player->GetState(IdleThrow)->countPressKey == 1 && player->GetApples() > 0)
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


void PlayerIdleState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = Player::GetInstance();
	
	if (player->isInjured)
	{
		player->SetVx(0);
		player->InjuredByOther(impactor);
	}
}

PlayerState::State PlayerIdleState::GetStateName()
{
	return Idle;
}

void PlayerIdleState::ResetState(int dummy)
{
	auto player = playerData->player;
	//	collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-16);
	player->SetColliderRight(19);
	player->SetColliderTop(25);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}

