#include "Stone.h"

Stone::Stone()
{
	Obstacles();
	SetTag(STONE);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_STONE, "Resources/Items/stone.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->AddFrames(textures->GetTexture(TEX_STONE), 1, 8, 0.25f, D3DCOLOR_XRGB(255, 255, 255));
}

Stone::~Stone()
{
}

void Stone::Update(float dt)
{
	if (animation->GetCurrentFrameID() == 0 || animation->GetCurrentFrameID() == 4)
		animation->SetDefaultTime(1.5f);
	else
		animation->SetDefaultTime(0.25f);

	if (animation->GetCurrentFrameID() == 4)
		isCollidable = true;
	else
		isCollidable = false;
	animation->Update(dt);
}

void Stone::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
