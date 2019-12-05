#pragma once
#include "Obstacles.h"
#include "Grid.h"

Obstacles::Obstacles() : Entity()
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

void Obstacles::SetSpawnBox(BoxCollider box, int id)
{
	spawnBox = box;
	position = D3DXVECTOR3(box.getCenter());
	this->id = id;
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

BoxCollider Obstacles::GetSpawnBox()
{
	return spawnBox;
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

void Obstacles::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active)
		Spawn();
	else
		MakeInactive();
}

void Obstacles::MakeInactive()
{
	isActived = false;
}

void Obstacles::Spawn()
{
	isActived = true;
}

Animation* Obstacles::GetAnimation()
{
	return animation;
}

void Obstacles::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
