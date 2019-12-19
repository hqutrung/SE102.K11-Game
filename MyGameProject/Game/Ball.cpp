#include "Ball.h"

Ball::Ball() : Obstacles() {
	SetTag(BALL);
	Textures* textures = Textures::GetInstance();
	animation->AddFramesA(textures->GetTexture(TEX_OBSTACLES), 1, 1, 1, 28, 28, 2, 28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

void Ball::Update(float dt)
{
	if (delayTime <= 0)
	{
		int frameID = animation->GetCurrentFrameID();
		if (frameID == 12 || frameID == 13 || frameID == 14 || frameID == 15 || frameID == 16)
		{
			isCollidable = true;
		}
		else isCollidable = false;

		animation->Update(dt);
		return;
	}
	delayTime -= dt;
}

void Ball::SetSpawnBox(BoxCollider box, int id)
{
	Obstacles::SetSpawnBox(box, id);
	if (id == 2)
		delayTime = animation->GetDefaultTime() * 14;
	else if (id == 1)
		delayTime = animation->GetDefaultTime() * 7;
	else
		delayTime = 0;
	collider.top = -4;
	collider.left = -1;
	collider.bottom = -31;
	collider.right = 27;
}
