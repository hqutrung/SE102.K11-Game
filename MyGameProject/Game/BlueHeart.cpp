#include "BlueHeart.h"

BlueHeart::BlueHeart() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_HEART, "Resources/Items/blueheart.png", D3DCOLOR_XRGB(255, 255, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_HEART), 1, 8, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_HEART)->GetLevelDesc(0, &desc);
	width = desc.Width / 8;
	height = desc.Height;
}

BlueHeart::~BlueHeart()
{
}

void BlueHeart::Update(float dt)
{
	animation->Update(dt);
}

void BlueHeart::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
