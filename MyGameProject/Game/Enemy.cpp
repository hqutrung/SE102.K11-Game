#include "Enemy.h"
#include"EnemyData.h"

Enemy::Enemy()
{
	SetType(EnemyType);
	SetStatic(false);
	SetActive(false);
	animation = new Animation(0.1f);
	enemyData = new EnemyData();
	enemyData->enemy = this;
}

Enemy::~Enemy()
{
	
}

void Enemy::Update(float dt)
{
	Entity::Update(dt);
	enemyData->enemyState->Update(dt);
}

void Enemy::Render()
{
	enemyData->enemyState->Render();
}

void Enemy::SetSpawnBox(BoxCollider box, int direction)
{
	spawnBox = box;
	spawnPosition = D3DXVECTOR3(box.getCenter());
	spawnDirection = (MoveDirection)direction;
	MakeInactive();
}

BoxCollider Enemy::GetRect()
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

BoxCollider Enemy::GetSpawnBox()
{
	return spawnBox;
}

Entity::MoveDirection Enemy::GetSpawnDirection()
{
	return spawnDirection;
}

void Enemy::SetRect(BoxCollider box)
{
	collider = box;
}

float Enemy::GetWidth()
{
	return collider.right - collider.left;
}

float Enemy::GetBigWidth()
{
	return width;
}

float Enemy::GetHeight()
{
	return collider.top - collider.bottom;
}

float Enemy::GetBigHeight()
{
	return height;
}

void Enemy::SetActive(bool active)
{
	if (isActived == active)
		return;

	if (active)
		Spawn();
	else
		MakeInactive();
}

void Enemy::SetColliderTop(float top) {
	collider.top = top;
}

void Enemy::SetColliderLeft(float left) {
	collider.left = left;
}

void Enemy::SetColliderBottom(float bottom) {
	collider.bottom = bottom;
}

void Enemy::SetColliderRight(float right) {
	collider.right = right;
}

void Enemy::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}

void Enemy::Spawn()
{
	isActived = true;
	position = spawnPosition;
}

void Enemy::MakeInactive()
{
	isActived = false;
	position = spawnPosition;
	direction = spawnDirection;
	SetColliderTop((spawnBox.top - spawnBox.bottom) / 2.0f);
	SetColliderBottom(-collider.top);
	SetColliderLeft((spawnBox.left - spawnBox.right) / 2.0f);
	SetColliderRight(-collider.right);
}
