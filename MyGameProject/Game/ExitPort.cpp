#include "ExitPort.h"

ExitPort::ExitPort() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_EXITPORT, "Resources/Items/exitport.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_EXITPORT), BoxCollider());
}

ExitPort::~ExitPort()
{
}

void ExitPort::Update(float dt)
{
}

void ExitPort::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

