#include "PlayerDuckState.h"

PlayerDuckState::PlayerDuckState(PlayerData* data)
{

	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1010, "Resources/PlayerState/duck_after.png", D3DCOLOR_XRGB(255,0,255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1010), 1, 5, 0.08f, D3DCOLOR_XRGB(255,0,255));

}

PlayerDuckState::~PlayerDuckState()
{
}

void PlayerDuckState::Render()
{
	PlayerState::Render();

}

void PlayerDuckState::Update(float dt)
{
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	if (m_Animation->IsLastFrame(dt))
	{
		m_Animation->SetCurrentFrame(m_Animation->GetCurrentFrameID() - 1);
	}
	PlayerState::Update(dt);
}

void PlayerDuckState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	//duck->jump
	if (keyboard->GetKey(JUMP_ARROW))
	{
		player->SetState(Jump);
		return;
	}

	if (keyboard->GetKey(THROW_ARROW)&&player->GetState(DuckThrow)->countPressKey==1 && player->GetApples() > 0)
	{
		player->SetState(DuckThrow);
		return;
	}

	//duck->duckAttack
	if (keyboard->GetKey(ATTACK_ARROW) && player->GetState(DuckAttack)->countPressKey == 1)
	{
		player->SetState(DuckAttack);
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

	if (keyboard->GetKey(DOWN_ARROW) || keyboard->GetKeyDown(DOWN_ARROW))
	{
		return;
	}
	//duck->idle
	player->SetState(Idle);
}

void PlayerDuckState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerDuckState::GetStateName()
{
	return Duck;
}

void PlayerDuckState::ResetState(int dummy)
{
	auto player = playerData->player;
	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-17);
	player->SetColliderRight(30);
	player->SetColliderTop(7);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}

BoxCollider PlayerDuckState::GetBody()
{
	auto player = Player::GetInstance();
	BoxCollider box;
	if (player->GetMoveDirection() == Player::MoveDirection::LeftToRight)
		box = BoxCollider(player->GetPosition().y , player->GetPosition().x - 7, player->GetPosition().x + 12, player->GetPosition().y - 24);
	else
		box = BoxCollider(player->GetPosition().y , player->GetPosition().x - 12, player->GetPosition().x + 7, player->GetPosition().y - 24);
	return box;
}
