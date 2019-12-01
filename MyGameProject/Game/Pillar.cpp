#include "Pillar.h"

Pillar::Pillar() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_PILLAR, "Resources/Items/pillar.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_PILLAR), BoxCollider());
}

Pillar::~Pillar()
{
}

void Pillar::Update(float dt)
{
}

void Pillar::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Pillar::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
