#include "Enemy.h"

Enemy::Enemy() : Entity() {
	SetType(EnemyType);
	SetStatic(false);
	enemyData = new EnemyData();
	enemyData->enemy = this;
	auto textures = Textures::GetInstance();
	textures->Add(TEX_ENEMY, "Resources/Enemy/Enemy.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(2894, "Resources/Enemy/explosiveEnemy.png", D3DCOLOR_XRGB(255, 0, 255));
	eExplosive = new Animation();
	eExplosive->AddFrames(textures->GetTexture(2894), 1, 10, 0.05, D3DCOLOR_XRGB(255, 0, 255));
}

Enemy::~Enemy()
{

}

void Enemy::Update(float dt)
{
	if (!isActived)
		return;

	enemyData->enemyState->Update(dt);
	Entity::Update(dt);

	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}

void Enemy::Render()
{
	if (Hp > 0)
	{
		if (isActived)
			enemyData->enemyState->Render();
	}
	else eExplosive->Render(GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), 1);

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

void Enemy::SetState(EnemyState::eState state)
{
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

void Enemy::MakeInactive()
{
	isActived = false;
	position = spawnPosition;
	direction = spawnDirection;
	SetColliderTop((spawnBox.top - spawnBox.bottom) / 2.0f);
	SetColliderBottom(-collider.top);
	SetColliderLeft((spawnBox.left - spawnBox.right) / 2.0f);
	SetColliderRight(-collider.left);
}

void Enemy::Spawn()
{
	isActived = true;
	position = spawnPosition;
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}

void Enemy::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
}
