#include "BlueVase.h"

BlueVase::BlueVase()
{
	Obstacles();
	SetTag(BLUEVASE);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BLUEVASE, "Resources/Items/bluevase.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_BLUEVASE), 1, 17, 0.15f, D3DCOLOR_XRGB(255, 0, 255));
}

BlueVase::~BlueVase()
{
}

void BlueVase::Update(float dt)
{
	if (animation->GetCurrentFrameID()==16)
		animation->SetDefaultTime(3.0f);
	else
		animation->SetDefaultTime(0.15f);
	animation->Update(dt);
}

void BlueVase::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
