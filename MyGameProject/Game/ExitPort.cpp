#include "ExitPort.h"

ExitPort::ExitPort() : Surface() {
	SetTag(EXITPORT);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_EXITPORT, "Resources/Items/exitport.png", D3DCOLOR_XRGB(255, 0, 255));
	sprite = new Sprites(textures->GetTexture(TEX_EXITPORT), BoxCollider());
}

ExitPort::~ExitPort()
{
}

void ExitPort::SetSpawnBox(BoxCollider box)
{
	Surface::SetSpawnBox(box);
	SetColliderBottom(-40);
}

