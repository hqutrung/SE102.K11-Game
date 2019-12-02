#include "ChainedPillar.h"

ChainedPillar::ChainedPillar()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_CHAINEDPILLAR, "Resources/Items/chainedpillar.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_CHAINEDPILLAR), BoxCollider());
	SetType(Surface);
	SetTag(CHAINEDPILLAR);
	SetStatic(true);
}

ChainedPillar::~ChainedPillar()
{
}

void ChainedPillar::Update(float dt)
{
}

void ChainedPillar::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void ChainedPillar::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
