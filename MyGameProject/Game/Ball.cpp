#include "Ball.h"

Ball::Ball()
{
	Obstacles();
	SetTag(BALL);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BALL, "Resources/Items/ball.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_BALL), 1, 28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
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
