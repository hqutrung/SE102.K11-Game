#include "JafarExplosion.h"

JafarExplosion::JafarExplosion(D3DXVECTOR3 pos) : Effect(pos)
{
	Textures* texs = Textures::GetInstance();
	texs->Add(TEX_JAFAR_EXPLOSION, "Resources/Explosive/jafarExplosive.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation();
	animation->AddFrames(texs->GetTexture(TEX_JAFAR_EXPLOSION), 2, 7, 0.06f);
}
