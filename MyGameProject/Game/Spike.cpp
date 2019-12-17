#include "Spike.h"

Spike::Spike() : Obstacles() {
	SetTag(SPIKE);
	Textures* textures = Textures::GetInstance();
	animation->AddFramesA(textures->GetTexture(TEX_OBSTACLES), 2, 11, 2, 21, 21, 2, 28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	isCollidable = false;
}

Spike::~Spike()
{
}

void Spike::Update(float dt)
{
	if (animation->GetCurrentFrameID() == 1 && isActived)
		Sound::GetInstance()->PlayFX(SPIKES);
	if (delayTime <= 0)
	{
		if (animation->GetCurrentFrameID() == 0)
			animation->SetDefaultTime(2.5f);
		else if(animation->GetCurrentFrameID() > 0 && animation->GetCurrentFrameID() < 5)
			animation->SetDefaultTime(0.01f);
		else if (animation->GetCurrentFrameID() == 5) {
			isCollidable = true;
			animation->SetDefaultTime(1.0f);
		}
		else
			animation->SetDefaultTime(0.1f);

		if (animation->GetCurrentFrameID() != 5) {
			isCollidable = false;
		}

		animation->Update(dt);
		return;
	}
	delayTime -= dt;
}

void Spike::SetSpawnBox(BoxCollider box, int id)
{
	Obstacles::SetSpawnBox(box, id);
	delayTime = (id == 1) ? 1.94f : 0;
	collider.top = 10;
	collider.left = -0;
	collider.bottom = -10;
	collider.right = 38;
}
