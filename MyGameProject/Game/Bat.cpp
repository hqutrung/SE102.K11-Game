#include "Bat.h"

Bat::Bat()
{
	SetTag(FATGUARD);
	batFollowPlayerState = new BatFollowPlayerState(enemyData);
	point = 100;
}

Bat::~Bat()
{
}

void Bat::Update(float dt)
{
	D3DXVECTOR3 target = Player::GetInstance()->GetPosition();


	Enemy::Update(dt);
}

void Bat::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
}

void Bat::SetState(EnemyState::eState state)
{
	if ((state == EnemyState::Follow))
		enemyData->enemyState = batFollowPlayerState;
	enemyData->enemyState->ResetState();
}

void Bat::Spawn()
{
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
