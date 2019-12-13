#include "AppleWeapon.h"

AppleWeapon::AppleWeapon() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_APPLE_WEAPON, "Resources/Weapons/1.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFramesA(textures->GetTexture(TEX_APPLE_WEAPON), 1, 1, 1, 4, 4, 1, 4, 0.1f);
	tag = PLAYERWEAPON;
	accelery = D3DXVECTOR2(0, 0);
}

void AppleWeapon::Update(float dt)
{
	Weapon::Update(dt);

	accelery.y -= 50 * dt;
	AddVelocity(accelery);
}

void AppleWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	if (!isDissapeared) {
		auto impactorTag = impactor->GetTag();
		auto impactorType = impactor->GetType();
		if (impactorType == Layer::EnemyType || impactorTag == SKELETONWEAPON
			|| impactorTag == GROUND || impactorTag == WALL) {
			OnDestroy();
		}
	}
}

void AppleWeapon::Instantiate(D3DXVECTOR3 position)
{
	accelery = D3DXVECTOR2(0, 0);
	if(Player::GetInstance()->GetCurrentState()->GetStateName() == PlayerState::RunThrow || Player::GetInstance()->GetPrevStateName() == PlayerState::JumpCross)
		SetVx(400);
	else
		SetVx(300);

	if (Player::GetInstance()->GetPosition().x > position.x)
	{
		if (Player::GetInstance()->GetCurrentState()->GetStateName() == PlayerState::RunThrow || Player::GetInstance()->GetPrevStateName() == PlayerState::JumpCross)
			SetVx(-400);
		else
			SetVx(-300);
	}
	SetVy(-9.8f);
	SetVelocity(velocity);

	SetColliderLeft(-4);
	SetColliderRight(4);
	SetColliderTop(4);
	SetColliderBottom(-4);

	Weapon::Instantiate(position);
}

void AppleWeapon::OnDestroy()
{
	EffectChain* effect = new EffectChain(new AppleWeaponExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
}
