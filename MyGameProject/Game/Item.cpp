#include "Item.h"

Item::Item()
{
	isDisappeared = false;
	isActived = false;
}

Item::~Item()
{
}

void Item::Update(float dt)
{
}

void Item::Render()
{
}

void Item::SetColliderTop(int top) {
	collider.top = top;
}

void Item::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -left;
}

void Item::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Item::SetColliderRight(int right) {
	collider.right = right;
}

void Item::ResetState()
{
	
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

float Item::GetWidth()
{
	return collider.right - collider.left;
}

float Item::GetHeight()
{
	return collider.top - collider.bottom;
}

void Item::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active && !isDisappeared)
		Spawn();
	else
		isActived = false;
}

void Item::Spawn()
{
	isActived = true;
}




