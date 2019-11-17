#include "Ball.h"

Ball::Ball(): Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BALL, "Resources/Items/ball.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_BALL), BoxCollider());
}

Ball::~Ball()
{
}

void Ball::Update(float dt)
{
}

void Ball::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
