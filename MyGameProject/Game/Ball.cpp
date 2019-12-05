#include "Ball.h"

Ball::Ball()
{
	Obstacles();
	SetTag(BALL);
	Textures* textures = Textures::GetInstance();
	animation->AddFramesA(textures->GetTexture(TEX_OBSTACLES), 1,1,1,28,28,2,28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

Ball::~Ball()
{
}

void Ball::Update(float dt)
{

		animation->Update(dt);
}

void Ball::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
