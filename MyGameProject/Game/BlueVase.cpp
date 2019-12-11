#include "BlueVase.h"

BlueVase::BlueVase() : Obstacles() {
	SetTag(BLUEVASE);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BLUEVASE, "Resources/Items/bluevase.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_BLUEVASE), 1, 17, 0.085f, D3DCOLOR_XRGB(255, 0, 255));
	isCollidable = false;
}

BlueVase::~BlueVase()
{
}

void BlueVase::Update(float dt)
{
	if (IsCollidable()) {
		if (animation->GetCurrentFrameID() == 16)
		{
			//Player::GetInstance()->SetLastPos(this->GetPosition());
			isCollidable = false;
			return;
		}
		else
			animation->SetDefaultTime(0.085f);
		animation->Update(dt);
	}
}
