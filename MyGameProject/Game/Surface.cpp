#include "Surface.h"

Surface::Surface()
{
	SetType(Layer::Surface);
	SetStatic(true);
}

Surface::~Surface()
{
}

void Surface::Render()
{
	sprite->Draw(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void Surface::SetSpawnBox(BoxCollider box)
{
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

void Surface::SetColliderTop(int top)
{
	collider.top = top;
}

void Surface::SetColliderLeft(int left)
{
	collider.left = left;
}

void Surface::SetColliderBottom(int bottom)
{
	collider.bottom = bottom;
}

void Surface::SetColliderRight(int right)
{
	collider.right = right;
}

BoxCollider Surface::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}
