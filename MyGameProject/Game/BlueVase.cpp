#include "BlueVase.h"

BlueVase::BlueVase() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BLUEVASE, "Resources/Items/bluevase.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_BLUEVASE), 1, 17, 0.15f, D3DCOLOR_XRGB(255, 0, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_BLUEVASE)->GetLevelDesc(0, &desc);
	width = desc.Width / 17;
	height = desc.Height;
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

void BlueVase::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
