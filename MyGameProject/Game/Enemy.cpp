#include "Enemy.h"

Enemy::Enemy()
{
	isActived = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
}

void Enemy::Render()
{
}

void Enemy::SetSpawnBox(BoxCollider box, int direction)
{
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
	spawnDirector = (MoveDirection)direction;
}

BoxCollider Enemy::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

float Enemy::GetWidth()
{
	return collider.right - collider.left;
}

float Enemy::GetHeight()
{
	return collider.top - collider.bottom;
}

void Enemy::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active && !isDisappeared)
		Spawn();
	else
		isActived = false;
}

void Enemy::Spawn()
{
	isActived = true;
}
