#include "SnakeJafarWeapon.h"
#include "Jafar.h"

SnakeJafarWeapon::SnakeJafarWeapon() : Weapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SNAKE_WEAPON, "Resources/Weapons/snakeWeapon.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_SNAKE_WEAPON), 1, 8, 0.1f);
	tag = SNAKEWEAPON;
	type = eWeapon;
}

void SnakeJafarWeapon::Update(float dt)
{
	Weapon::Update(dt);
	if (position.y <= Jafar::GetInstance()->GetPosition().y - 35)
		SetVy(0);
}

void SnakeJafarWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	if (!isDissapeared) {
		auto impactorTag = impactor->GetTag();
		auto impactorType = impactor->GetType();
		if (impactorTag == WALL) {
			OnDestroy();
		}
	}
}

void SnakeJafarWeapon::Instantiate(D3DXVECTOR3 position)
{
	auto playerState = Player::GetInstance()->GetCurrentState()->GetStateName();
	auto playerPos = Player::GetInstance()->GetPosition();

	SetVx(200);
	SetVy(-50);

	if (playerPos.x < position.x)
		SetVx(-velocity.x);

	SetColliderLeft(-20);
	SetColliderRight(30);
	SetColliderTop(4);
	SetColliderBottom(-24);

	Weapon::Instantiate(position);
}

void SnakeJafarWeapon::OnDestroy()
{
	SetActive(false);
	isDissapeared = true;
}
