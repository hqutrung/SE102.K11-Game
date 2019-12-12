#include "Weapon.h"

Weapon::Weapon()
{
	SetType(Layer::Weapon);
}

Weapon::~Weapon()
{
}

void Weapon::Update(float dt)
{
	anim->Update(dt);
	Entity::Update(dt);
}

void Weapon::Render()
{
	anim->Render(position);
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
	if (active)
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

void Weapon::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
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
	anim->ResetAnimation();
	isActived = true;
}
