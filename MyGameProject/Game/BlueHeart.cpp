#include "BlueHeart.h"

BlueHeart::BlueHeart()
{
	Item();
	SetTag(BLUEHEART);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_HEART, "Resources/Items/blueheart.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_HEART), 1, 8, 0.1f, D3DCOLOR_XRGB(255, 0, 255));

}

BlueHeart::~BlueHeart()
{
}

void BlueHeart::Update(float dt)
{
	animation->Update(dt);
}

void BlueHeart::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
