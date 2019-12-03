#include "Item.h"

Item::Item()
{
	isDisappeared = false;
	SetStatic(true);
	SetType(ItemType);
	animation = new Animation(0.1f);
}

Item::~Item()
{
}

void Item::Update(float dt)
{
}

void Item::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Item::SetColliderTop(int top) {
	collider.top = top;
}

void Item::SetColliderLeft(int left) {
	collider.left = left;
}

void Item::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Item::SetColliderRight(int right) {
	collider.right = right;
}


void Item::SetSpawnBox(BoxCollider box)
{
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

BoxCollider Item::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

void Item::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active && !isDisappeared)
		Spawn();
	else
		MakeInactive();
}

void Item::MakeInactive()
{
	isActived = false;
}

void Item::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}

void Item::Spawn()
{
	isActived = true;
}




