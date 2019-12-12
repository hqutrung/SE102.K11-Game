#include "SkeletonWeapon.h"

SkeletonWeapon::SkeletonWeapon() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SKELETON_WEAPON, "Resources/Weapons/1.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_SKELETON_WEAPON), 1, 4, 0.1f);
	tag = SKELETONWEAPON;
	accelery = D3DXVECTOR2(0, 0);
}

void SkeletonWeapon::Update(float dt)
{
	Weapon::Update(dt);

	//accelery.y -= 50 * dt;
	//AddVelocity(accelery);
}

void SkeletonWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto impactorTag = impactor->GetTag();
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::EnemyType || impactorTag == PLAYERWEAPON
		|| impactorTag == GROUND || impactorTag == WALL) {
		OnDestroy();
	}
}

void SkeletonWeapon::Instantiate(D3DXVECTOR3 position)
{
	accelery = D3DXVECTOR2(0, 0);

	SetVy(-9.8f);
	SetVelocity(velocity);

	SetColliderLeft(-4);
	SetColliderRight(4);
	SetColliderTop(4);
	SetColliderBottom(-4);

	Weapon::Spawn();
}

void SkeletonWeapon::OnDestroy()
{
	isDissapeared = true;
	EffectChain* effect = new EffectChain(new AppleWeaponExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
}
