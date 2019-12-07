#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1268, "Resources/PlayerState/injured_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1268), 1, 6, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

void PlayerInjuredState::Render()
{
	PlayerState::Render();
}

void PlayerInjuredState::Update(float dt)
{
	auto player = Player::GetInstance();

	if (m_Animation->IsLastFrame(dt))
		player->SetState(Idle);
	PlayerState::Update(dt);
}

void PlayerInjuredState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	if (m_Animation->GetCurrentFrameID() > 0) {
		if (keyboard->GetKeyDown(THROW_ARROW) && player->GetState(IdleThrow)->countPressKey == 1)
		{
			player->SetState(IdleThrow);
			return;
		}

		if (keyboard->GetKey(JUMP_ARROW) || keyboard->GetKeyDown(JUMP_ARROW))
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

		if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW) || keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
		{
			player->SetState(Run);
			return;
		}
	}
}

void PlayerInjuredState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
}

PlayerState::State PlayerInjuredState::GetStateName()
{
	return Injured;
}

void PlayerInjuredState::ResetState(int dummy)
{
	PlayerState::ResetState(dummy);
}
