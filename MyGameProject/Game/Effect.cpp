#include "Effect.h"

Effect::Effect(D3DXVECTOR3 pos)
{
	this->pos = pos;
}

Effect::~Effect()
{
}

bool Effect::Update(float dt)
{
	animation->Update(dt);
	if (animation->IsLastFrame(dt))
		return false;
	return true;
}

void Effect::Render()
{
	animation->Render(pos);
}
