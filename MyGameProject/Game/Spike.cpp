#include "Spike.h"

Spike::Spike() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_SPIKE, "Resources/Items/spike.png", D3DCOLOR_XRGB(255, 255, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_SPIKE), 1, 10, 0.2f, D3DCOLOR_XRGB(255, 255, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_SPIKE)->GetLevelDesc(0, &desc);
	width = desc.Width / 10;
	height = desc.Height;
}

Spike::~Spike()
{
}

void Spike::Update(float dt)
{
	if (animation->GetCurrentFrameID() == 0)
		animation->SetDefaultTime(2.0f);
	else if (animation->GetCurrentFrameID() == 5)
		animation->SetDefaultTime(1.0f);
	else if (animation->GetCurrentFrameID() == 6)
		animation->SetDefaultTime(0.25f);
	else
		animation->SetDefaultTime(0.01f);
	animation->Update(dt);
}

void Spike::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Spike::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
