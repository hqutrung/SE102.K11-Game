#include "AppleWeapon.h"
#include "Player.h"

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
		if (impactorType == Layer::EnemyType || impactorTag == GROUND || impactorTag == WALL) {
			OnDestroy();
		}
	}
}

void AppleWeapon::Instantiate(D3DXVECTOR3 position)
{
	accelery = D3DXVECTOR2(0, 0);
	auto playerState = Player::GetInstance()->GetCurrentState()->GetStateName();
	auto playerPos = Player::GetInstance()->GetPosition();

	SetVx((playerState == PlayerState::RunThrow || playerState == PlayerState::JumpCross) ? 400 : 300);
	
	if (playerPos.x > position.x)
		SetVx(-velocity.x);
	SetVy(0);

	SetColliderLeft(-4);
	SetColliderRight(5);
	SetColliderTop(5);
	SetColliderBottom(-4);

	Weapon::Instantiate(position);
}

void AppleWeapon::OnDestroy()
{
	DebugOut(L"[ONDESTROY]\n");
	Sound::GetInstance()->PlayFX(APPLE_EXPLOSIVE);
	EffectChain* effect = new EffectChain(new AppleWeaponExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	isDissapeared = true;
}
