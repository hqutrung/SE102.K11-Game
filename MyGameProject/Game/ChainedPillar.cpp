#include "ChainedPillar.h"

ChainedPillar::ChainedPillar() : Surface() {
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_CHAINEDPILLAR, "Resources/Items/chainedpillar.png", D3DCOLOR_XRGB(255, 255, 255));
	sprite = new Sprites(textures->GetTexture(TEX_CHAINEDPILLAR), BoxCollider());
	SetTag(CHAINEDPILLAR);
}

ChainedPillar::~ChainedPillar()
{
}
