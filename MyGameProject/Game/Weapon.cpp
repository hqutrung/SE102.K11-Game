#include "Weapon.h"

Weapon::Weapon() : Entity()
{
	SetType(Layer::pWeapon);
	animation = new Animation();
	isActived = false;
	isDissapeared = false;
}

Weapon::~Weapon()
{
}

void Weapon::Update(float dt)
{
	if (isActived) {
		animation->Update(dt);
		Entity::Update(dt);
	}
}

void Weapon::Render()
{
	animation->Render(position);
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
	DebugOut(L"[SETACTIVE]   appleWeapon->isActived: %d\n", active);
	if (isActived == active)
		return;
	if (active && !isDissapeared)
		//IS A BUG, INSTANTIATE WITH POSITION INSTEAD, BRO
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
	/*EffectChain* effect = new EffectChain(new Explosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	return EarnedData(point);*/
}

void Weapon::MakeInactive()
{
	isActived = false;
}

void Weapon::Spawn()
{
	//animation->ResetAnimation();
	isActived = true;
	isDissapeared = false;

	DebugOut(L"[SPAWN]   appleWeapon->isActived: %d\n", isActived);
}
