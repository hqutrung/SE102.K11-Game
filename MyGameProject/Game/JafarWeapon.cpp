#include "JafarWeapon.h"
#include "Player.h"
#include "Jafar.h"

JafarWeapon::JafarWeapon() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_JAFAR_WEAPON, "Resources/Weapons/jafarWeapon.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_JAFAR_WEAPON), 1, 3, 0.1f);
	tag = JAFARWEAPON;
	type = eWeapon;
	time = 0;
}

void JafarWeapon::Update(float dt)
{
	time += dt;
	auto jafar = Jafar::GetInstance();
	auto player = Player::GetInstance();
	D3DXVECTOR3 target = player->GetPosition();
	D3DXVECTOR3 target1 = jafar->GetPosition();
	D3DXVECTOR2 weaponVeclocity;
	if (jafar->GetDisToPlayer().x < 0) {
		target.x += player->GetCollider().right;
		target1.x += 100;
	}
	else {
		target.x += player->GetCollider().left;
		target1.x -=100;
	}
	//if (player->GetStatus() == Player::Jumping || player->GetStatus() == Player::Falling) {
	if(player->GetBody().bottom > 100){
		target.y += player->GetCollider().top;

		weaponVeclocity = D3DXVECTOR2(target - GetPosition());
		D3DXVec2Normalize(&weaponVeclocity, &weaponVeclocity);
		SetVelocity(weaponVeclocity * 300);

		int dau = rand() & 1 ? -1 : 1;
		int index = ((float)(rand() % (100 - 30 + 1)) + 30) * dau;
		AddVy(index);
	}
	else
	{
		target1.y -= 30;
		target.y += player->GetCollider().bottom;
		if((position.x < target1.x && jafar->GetDisToPlayer().x < 0) || (position.x > target1.x && jafar->GetDisToPlayer().x > 0))
			weaponVeclocity = D3DXVECTOR2(target1 - GetPosition());
		else
			weaponVeclocity = D3DXVECTOR2(target - GetPosition());
		D3DXVec2Normalize(&weaponVeclocity, &weaponVeclocity);
		SetVelocity(weaponVeclocity * 300);
	}

	Weapon::Update(dt);

}

void JafarWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	if (!isDissapeared) {
		auto impactorTag = impactor->GetTag();
		auto impactorType = impactor->GetType();
		if (impactorTag == PLAYER) {
			OnDestroy();
		}
	}
}

void JafarWeapon::Instantiate(D3DXVECTOR3 position)
{
	auto playerState = Player::GetInstance()->GetCurrentState()->GetStateName();
	auto playerPos = Player::GetInstance()->GetPosition();

	position.y += 10;
	if (playerPos.x > position.x)
		position.x += Jafar::GetInstance()->GetCollider().right + 15;
	else
		position.x += Jafar::GetInstance()->GetCollider().left - 15;

	SetColliderLeft(-12);
	SetColliderRight(12);
	SetColliderTop(24);
	SetColliderBottom(-27);

	Weapon::Instantiate(position);
	Sound::GetInstance()->PlayFX(JAFAR_TRACTOR);
}

void JafarWeapon::OnDestroy()
{
	EffectChain* effect = new EffectChain(new SkeletonWeaponExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	isDissapeared = true;
}
