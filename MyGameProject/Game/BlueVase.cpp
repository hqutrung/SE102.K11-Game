#include "BlueVase.h"
#include "Player.h"

BlueVase::BlueVase() : Obstacles() {
	SetTag(BLUEVASE);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BLUEVASE, "Resources/Items/bluevase.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_BLUEVASE), 1, 17, 0.085f, D3DCOLOR_XRGB(255, 0, 255));
	isCollidable = false;
}

void BlueVase::Update(float dt)
{
	if (IsCollidable()) {
		if (animation->IsLastFrame(dt))
		{
			isCollidable = false;
			return;
		}
		else
			animation->SetDefaultTime(0.085f);
		animation->Update(dt);
	}
}

void BlueVase::Render()
{
	auto player = Player::GetInstance();
	if (player->isReviving == true)
	{
		animation->ResetAnimation();
		isCollidable = true;
		return;
	}
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
