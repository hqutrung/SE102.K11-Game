#include "Ball.h"

Ball::Ball(): Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BALL, "Resources/Items/ball.png", D3DCOLOR_XRGB(255, 255, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_BALL), 1, 28, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_BALL)->GetLevelDesc(0, &desc);
	width = desc.Width / 28;
	height = desc.Height;
}

Ball::~Ball()
{
}

void Ball::Update(float dt)
{
	animation->Update(dt);
}

void Ball::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Ball::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
