#include "Obstacles.h"

Obstacles::Obstacles()
{
	SetStatic(true);
	SetType(ObstaclesType);
	animation = new Animation(0.1f);
}

Obstacles::~Obstacles()
{
}

void Obstacles::Update(float dt)
{
}

void Obstacles::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Obstacles::SetColliderTop(int top)
{
	collider.top = top;
}

void Obstacles::SetColliderLeft(int left)
{
	collider.left = left;
}

void Obstacles::SetColliderBottom(int bottom)
{
	collider.bottom = bottom;
}

void Obstacles::SetColliderRight(int right)
{
	collider.right = right;
}

void Obstacles::SetSpawnBox(BoxCollider box)
{
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

void Obstacles::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active && !isDisappeared)
		Spawn();
	else
		MakeInactive();
}

BoxCollider Obstacles::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

void Obstacles::MakeInactive()
{
	isActived = false;
}

void Obstacles::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}

void Obstacles::Spawn()
{
	isActived = true;
}
