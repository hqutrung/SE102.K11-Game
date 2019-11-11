#include "DemoRunningState.h"

DemoRunningState::DemoRunningState(DemoObjectData* data)
{
	this->demoObjectData = data;
	auto tex = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFrames(tex->GetTexture(TEX_DEMOOBJECT), 1, 4, 0.07f, D3DCOLOR_XRGB(255, 255, 255));
}

DemoRunningState::~DemoRunningState()
{
}

void DemoRunningState::Update(float dt)
{
	KeyBoard* keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
		demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCCITY, 0));
	else if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW))
			demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCCITY, 0));

	if(keyboard->GetKey(UP_ARROW) && !keyboard->GetKey(DOWN_ARROW))
		demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(0, PLAYER_RUN_VELOCCITY));
	else if (keyboard->GetKey(DOWN_ARROW) && !keyboard->GetKey(UP_ARROW))
		demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(0, -PLAYER_RUN_VELOCCITY));
	else
		demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(0, 0));

	DemoObjectState::Update(dt);
}

void DemoRunningState::Render()
{
	m_Animation->Render(demoObjectData->DemoObject->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), demoObjectData->DemoObject->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void DemoRunningState::HandleInput()
{
	//Slash, Left, Right, 
	KeyBoard* keyboard = KeyBoard::GetInstance();

	/*if (keyboard->GetKeyDown(SLASH_BUTTON)) {
		playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
		if (keyboard->GetKey(UP_ARROW))
			playerData->player->SetState(UseItem);
		else
			playerData->player->SetState(Slash);
	}
	else
		if (keyboard->GetKeyDown(JUMP_BUTTON)) {
			playerData->player->SetState(Jump);
		}
		else if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
			playerData->player->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCITY, 0));
		else if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW))
			playerData->player->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCITY, 0));
		else if (keyboard->GetKey(DOWN_ARROW)) {
			playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
			playerData->player->SetState(Crouch);
		}
		else {
			playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
			playerData->player->SetState(Idle);
		}*/

	if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
		demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCCITY, 0));
	else if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW))
		demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCCITY, 0));
	else {
		//demoObjectData->DemoObject->SetVelocity(D3DXVECTOR2(0, 0));
		//playerData->player->SetState(Idle);
	}
}

DemoObjectState::State DemoRunningState::GetState()
{
	return Running;
}
