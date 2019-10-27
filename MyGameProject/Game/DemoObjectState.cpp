#include "DemoObjectState.h"
#include  "DemoObject.h"

DemoObjectState::DemoObjectState()
{
}

DemoObjectState::DemoObjectState(DemoObjectData* data)
{
	this->demoObjectData = data;
}

void DemoObjectState::Update(float dt)
{
	m_Animation->Update(dt);
}

void DemoObjectState::Render()
{
	m_Animation->Render(demoObjectData->DemoObject->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), demoObjectData->DemoObject->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void DemoObjectState::HandleInput()
{
}

DemoObjectState::State DemoObjectState::GetState()
{
	return Running;
}

int DemoObjectState::GetAnimationHeight()
{
	return m_Animation->GetHeightCurrentFrame();
}

int DemoObjectState::GetAnimationWidth()
{
	return m_Animation->GetWidthCurrentFrame();
}

DemoObjectState::~DemoObjectState()
{
}
