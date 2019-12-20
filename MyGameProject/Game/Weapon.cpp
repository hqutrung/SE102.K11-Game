#include "Weapon.h"
#include "Player.h"

Weapon::Weapon() : Entity()
{
	SetType(Layer::pWeapon);
	animation = new Animation();
	isActived = false;
	isDissapeared = false;
}

Weapon::~Weapon()
{
	delete animation;
	animation = NULL;
}

void Weapon::Update(float dt)
{
	animation->Update(dt);
	Entity::Update(dt);
}

void Weapon::Render()
{
	if (Player::GetInstance()->GetPosition().x > position.x)
		animation->Render(position);
	else
		animation->Render(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), true);
}

BoxCollider Weapon::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;

	if (direction == Entity::LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
	return r;
}

void Weapon::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active && !isDissapeared)
		Spawn();
	else
		MakeInactive();
}

float Weapon::GetWidth()
{
	return collider.right - collider.left;
}

float Weapon::GetBigWidth()
{
	return width;
}

float Weapon::GetHeight()
{
	return collider.top - collider.bottom;
}

float Weapon::GetBigHeight()
{
	return height;
}

void Weapon::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
}

void Weapon::Instantiate(D3DXVECTOR3 position)
{
	this->position = position;
	Spawn();
}

void Weapon::OnDestroy()
{
}

void Weapon::MakeInactive()
{
	isActived = false;
}

void Weapon::Spawn()
{
	isActived = true;
	isDissapeared = false;
	animation->ResetAnimation();
}
