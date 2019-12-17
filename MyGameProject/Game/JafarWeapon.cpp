#include "JafarWeapon.h"
#include "Player.h"

JafarWeapon::JafarWeapon() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_JAFAR_WEAPON, "Resources/Weapons/jafarWeapon.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_JAFAR_WEAPON), 1, 3, 0.1f);
	tag = JAFARWEAPON;
	type = eWeapon;
}

void JafarWeapon::Update(float dt)
{
	Weapon::Update(dt);
}

void JafarWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	/*if (!isDissapeared) {
		auto impactorTag = impactor->GetTag();
		auto impactorType = impactor->GetType();
		if (impactorTag == WALL) {
			OnDestroy();
		}
	}*/
}

void JafarWeapon::Instantiate(D3DXVECTOR3 position)
{
	auto playerState = Player::GetInstance()->GetCurrentState()->GetStateName();
	auto playerPos = Player::GetInstance()->GetPosition();

	SetVx(300);

	if (playerPos.x < position.x)
		SetVx(-velocity.x);
	SetVy(0);

	SetColliderLeft(-12);
	SetColliderRight(12);
	SetColliderTop(24);
	SetColliderBottom(-27);

	Weapon::Instantiate(position);
}

void JafarWeapon::OnDestroy()
{
	SetActive(false);
	isDissapeared = true;
}
