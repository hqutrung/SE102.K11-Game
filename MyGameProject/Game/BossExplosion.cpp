#include "BossExplosion.h"

BossExplosion::BossExplosion(D3DXVECTOR3 pos)  : Effect(pos){
	Textures* texs = Textures::GetInstance();
	texs->Add(TEX_BIGITEM_EXPLOSION, "Resources/Explosive/jafarExplosive.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation();
	animation->AddFramesA(texs->GetTexture(TEX_BIGITEM_EXPLOSION), 1, 1, 2, 8, 10, 2, 10, 0.06f);
}
