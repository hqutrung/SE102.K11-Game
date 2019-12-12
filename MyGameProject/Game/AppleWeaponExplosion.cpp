#include "AppleWeaponExplosion.h"

AppleWeaponExplosion::AppleWeaponExplosion(D3DXVECTOR3 pos) : Effect(pos)
{
	Textures* texs = Textures::GetInstance();
	texs->Add(TEX_APPLE_WEAPON_EXPLOSION, "Resources/Explosive/explosiveSmallItem.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation(); 
	animation->AddFrames(texs->GetTexture(TEX_APPLE_WEAPON_EXPLOSION), 1, 12, 0.03f);
}
