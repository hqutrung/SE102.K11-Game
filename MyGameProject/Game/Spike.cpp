#include "Spike.h"

Spike::Spike() : Obstacles() {
	SetTag(SPIKE);
	Textures* textures = Textures::GetInstance();
	animation->AddFramesA(textures->GetTexture(TEX_OBSTACLES), 2, 11, 2, 21, 28, 2, 28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

Spike::~Spike()
{
}

void Spike::Update(float dt)
{
	if (delayTime <= 0)
	{
		if (animation->GetCurrentFrameID() == 0)
			animation->SetDefaultTime(2.5f);
		else if(animation->GetCurrentFrameID() > 0 && animation->GetCurrentFrameID() < 5)
			animation->SetDefaultTime(0.01f);
		else if (animation->GetCurrentFrameID() == 5)
			animation->SetDefaultTime(1.0f);
		else
			animation->SetDefaultTime(0.1f);
		animation->Update(dt);
		return;
	}
	delayTime -= dt;
}

void Spike::SetSpawnBox(BoxCollider box, int id)
{
	Obstacles::SetSpawnBox(box, id);
	if (id == 1)
		delayTime = 1.94f;
	else
		delayTime = 0;
}

void Spike::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
