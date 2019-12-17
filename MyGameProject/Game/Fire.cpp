#include "Fire.h"
#include "Jafar.h"

Fire::Fire() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_FIRE, "Resources/Weapons/fire.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_FIRE), 1, 5, 0.05f);
	tag = FIRE;
	type = eWeapon;
}

void Fire::Update(float dt)
{
	Weapon::Update(dt);
	bool isCol = CollisionDetector::IsCollide(GetRect(), Jafar::GetInstance()->GetRect());
	if ((animation->IsLastFrame(dt) && !isCol) || Jafar::GetInstance()->isDied)
		OnDestroy();
}

void Fire::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	/*if (!isDissapeared) {
		auto impactorTag = impactor->GetTag();
		auto impactorType = impactor->GetType();
		if (impactorTag == PLAYER && animation->IsLastFrame(dt)) {
			OnDestroy();
		}
	}*/
}

void Fire::Instantiate(D3DXVECTOR3 position)
{
	auto playerState = Player::GetInstance()->GetCurrentState()->GetStateName();
	auto playerPos = Player::GetInstance()->GetPosition();

	SetVx(0);
	SetVy(0);

	SetColliderLeft(-30);
	SetColliderRight(35);
	SetColliderTop(25);
	SetColliderBottom(-25);

	Weapon::Instantiate(position);
}

void Fire::OnDestroy()
{
	SetActive(false);
	isDissapeared = true;
}
