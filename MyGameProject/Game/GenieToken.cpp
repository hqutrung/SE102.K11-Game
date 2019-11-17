#include "GenieToken.h"

GenieToken::GenieToken() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_GENIETOKEN, "Resources/Items/genietoken.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_GENIETOKEN), BoxCollider());
}

GenieToken::~GenieToken()
{
}

void GenieToken::Update(float dt)
{
}

void GenieToken::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}
