#include "BlueHeart.h"

BlueHeart::BlueHeart() : Item()
{
	SetTag(BLUEHEART);
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_HEART, "Resources/Items/blueheart.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_HEART), 1, 8, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	points = 150;
}

void BlueHeart::OnDestroy()
{
	Item::OnDestroy();
	Sound::GetInstance()->PlayFX(HEART_COLLECT);
	if (Player::GetInstance()->GetHp() < 9)
		Player::GetInstance()->AddHp();
	Player::GetInstance()->isBonusHp = true;
}
