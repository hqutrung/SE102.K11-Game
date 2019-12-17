#include "Apple.h"

Apple::Apple() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_APPLE, "Resources/Items/apple.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_APPLE), 1, 1, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	SetTag(APPLE);
}

Apple::~Apple()
{
	
}

void Apple::Update(float dt)
{
}

void Apple::OnDestroy()
{
	Item::OnDestroy();
	Sound::GetInstance()->PlayFX(APPLE_COLLECT);
	Player::GetInstance()->AddApples();
}
