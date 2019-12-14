#include "SkeletonWeaponExplosion.h"

SkeletonWeaponExplosion::SkeletonWeaponExplosion(D3DXVECTOR3 pos) : Effect(pos)
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SKELETON_WEAPON_EXPLOSION, "Resources/Explosive/explosiveSkeletonWeapon.png", D3DCOLOR_XRGB(255, 0, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_SKELETON_WEAPON_EXPLOSION), 1, 4, 0.05f);
}
