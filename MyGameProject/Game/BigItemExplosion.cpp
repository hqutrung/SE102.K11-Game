#include "BigItemExplosion.h"

BigItemExplosion::BigItemExplosion(D3DXVECTOR3 pos) : Effect(pos)
{
	Textures* texs = Textures::GetInstance();
	texs->Add(TEX_ENEMY_EXPLOSION, "Resources/Explosive/explosiveEnemy.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation();
	animation->AddFrames(texs->GetTexture(TEX_ENEMY_EXPLOSION), 1, 10, 0.1f);
}
