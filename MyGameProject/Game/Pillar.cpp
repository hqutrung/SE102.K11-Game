#include "Pillar.h"

Pillar::Pillar(int id)
{
	Textures* textures = Textures::GetInstance();
	Item();
	switch (id)
	{
	case 1:
		textures->Add(TEX_PILLAR + 1, "Resources/Items/pillar1.png", D3DCOLOR_XRGB(255, 255, 255));
		SetTag(PILLAR1);
		break;
	case 2:
		textures->Add(TEX_PILLAR + 2, "Resources/Items/pillar2.png", D3DCOLOR_XRGB(255, 255, 255));
		SetTag(PILLAR2);
		break;
	case 3:
		textures->Add(TEX_PILLAR + 3, "Resources/Items/pillar3.png", D3DCOLOR_XRGB(255, 255, 255));
		SetTag(PILLAR3);
		break;
	case 4:
		textures->Add(TEX_PILLAR + 4, "Resources/Items/pillar4.png", D3DCOLOR_XRGB(255, 255, 255));
		SetTag(PILLAR4);
		break;
	}
	sprite = new Sprites(textures->GetTexture(TEX_PILLAR + id), BoxCollider());
	SetType(Surface);
	SetStatic(true);
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
