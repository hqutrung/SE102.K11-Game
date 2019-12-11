#include "Surface.h"

Surface::Surface() : Entity()
{
	SetType(Layer::Surface);
	SetStatic(true);
}

Surface::~Surface()
{
}

void Surface::Render()
{
	sprite->Draw(position);
}

void Surface::SetSpawnBox(BoxCollider box)
{
	spawnBox = box;
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

BoxCollider Surface::GetSpawnBox()
{
	return spawnBox;
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
