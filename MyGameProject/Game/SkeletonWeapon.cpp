#include "SkeletonWeapon.h"

SkeletonWeapon::SkeletonWeapon() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SKELETON_WEAPON, "Resources/Weapons/skeletonWeapon.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_SKELETON_WEAPON), 1, 4, 0.1f);
	type = Layer::eWeapon;
	tag = SKELETONWEAPON;
	accelery = D3DXVECTOR2(0, 0);
}

void SkeletonWeapon::Update(float dt)
{
	Weapon::Update(dt);
	if (isCollideWithWall)
		velocity = -velocity;
	AddVelocity(D3DXVECTOR2(0, -3.0f));
}

void SkeletonWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	isCollideWithWall = false;
	auto impactorTag = impactor->GetTag();
	auto impactorType = impactor->GetType();
	D3DXVECTOR2 newVelocity = velocity;
	if (impactorTag == GROUND || impactorTag == WALL) {
		if (side == Right || side == Left)
			newVelocity.x *= collisionTime;
		if (side == Bottom)
			newVelocity.y *= collisionTime;
		/*if (side == Bottom)
			SetVy(-velocity.y);
		if (side == Right || side == Left)
			SetVx(-velocity.x);*/
		if (collisionTime > 0) {
			velocity = newVelocity;
			isCollideWithWall = true;
		}
	}

	if (impactorType == PlayerType)
	{
		this->OnDestroy();
	}

}
void SkeletonWeapon::Instantiate(D3DXVECTOR3 position)
{
	accelery = D3DXVECTOR2(0, 0);


	int dau = rand() & 1 ? -1 : 1;
	velocity.x = (float)(rand() % (200 - 100 + 1)) + 100 * dau;
	velocity.y = (float)(rand() % (450 - 50 + 1)) + 50;

	int botPos = (int)position.y - 35;
	int topPos = (int)position.y + 20;
	position.y = (float)(rand() % (topPos - botPos + 1)) + botPos;

	SetColliderLeft(-4);
	SetColliderRight(4);
	SetColliderTop(4);
	SetColliderBottom(-4);

	this->position = position;
	Weapon::Spawn();
}

void SkeletonWeapon::OnDestroy()
{
	EffectChain* effect = new EffectChain(new SkeletonWeaponExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	isDissapeared = true;
}
