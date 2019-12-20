#include "Apple.h"

Apple::Apple() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_APPLE, "Resources/Items/apple.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_APPLE), 1, 1, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	SetTag(APPLE);
	points = 0;
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

void Apple::SetSpawnBox1(int top, int left, int bot, int right)
{
	auto box = BoxCollider(top, left, right, bot);
	spawnBox = box;
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}
