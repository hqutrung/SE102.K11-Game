#include "ExitPort.h"

ExitPort::ExitPort()
{
	Surface();
	SetTag(EXITPORT);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_EXITPORT, "Resources/Items/exitport.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_EXITPORT), BoxCollider());
}

ExitPort::~ExitPort()
{
}

