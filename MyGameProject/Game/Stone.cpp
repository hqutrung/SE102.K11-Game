#include "Stone.h"

Stone::Stone()
{
	Obstacles();
	SetTag(STONE);

	Textures* textures = Textures::GetInstance();
	animation->AddFramesA(textures->GetTexture(TEX_OBSTACLES), 2, 1, 2, 9, 28,2,28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
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
