#include "DemoObject.h"
#include "Textures.h"
#include "DemoRunningState.h"

DemoObject* DemoObject::instance = NULL;

DemoObject* DemoObject::GetInstance()
{
	if (!instance)
		instance = new DemoObject();
	return instance;
}

DemoObject::DemoObject(): Entity()
{
	instance = this;

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_DEMOOBJECT, "Resources/aladin.png", D3DCOLOR_XRGB(255, 163, 177));

	demoObjectData = new DemoObjectData();
	demoObjectData->DemoObject = this;

	runningState = new DemoRunningState(demoObjectData);

	SetState(DemoObjectState::Running);

	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_DEMOOBJECT)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;

	SetActive(true);
}

DemoObject::~DemoObject()
{
}

void DemoObject::Update(float dt)
{
	Entity::Update(dt);
	if (demoObjectData->state)
		demoObjectData->state->Update(dt);
}

void DemoObject::Render()
{
	demoObjectData->state->Render();
}

void DemoObject::HandleInput()
{
	if (this->demoObjectData->state)
		demoObjectData->state->HandleInput();
}

DemoObjectState::State DemoObject::GetState()
{
	return demoObjectData->state->GetState();
}

void DemoObject::SetMoveDirection(Entity::MoveDirection dir)
{
	if (dir == direction)
		return;
	direction = dir;
}

void DemoObject::SetState(DemoObjectState::State name, int dummy)
{
	switch (name) {
	case DemoObjectState::Running:
		demoObjectData->state = runningState;
		break;

	}

	//currentState = demoObjectData->state->GetState();

	/*case DemoObjectState::Idle:
		demoObjectData->state = idleState;
		break;
	case PlayerState::Slash:
		playerData->state = slashState;
		break;
	case PlayerState::Crouch:
		playerData->state = crouchState;
		break;
	case PlayerState::CrouchSlash:
		playerData->state = crouchSlashState;
		break;
	case PlayerState::Climb:
		playerData->state = climbState;
		break;
	case PlayerState::UseItem:
		playerData->state = useItemState;
		CheckForUseItem();
		break;
	case PlayerState::Jump:
		playerData->state = jumpState;
		break;
	case PlayerState::Falling:
		playerData->state = jumpState;
		dummy = 1;
		break;
	case PlayerState::Injured:
		playerData->state = injuredState;
		break;*/
}
