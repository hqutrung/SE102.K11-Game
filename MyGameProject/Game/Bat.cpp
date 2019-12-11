#include "Bat.h"

Bat::Bat() : Enemy()
{
	SetTag(BAT);
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BAT, "Resources/Enemy/bat.png", D3DCOLOR_XRGB(255, 255, 255));
	batFollowPlayerState = new BatFollowPlayerState(enemyData);
	batIdleState = new BatIdleState(enemyData);
	point = 100;
	isCollidable = true;
	Hp = 1;
	isAttack = true;
}

Bat::~Bat()
{
}

void Bat::Update(float dt)
{
	auto enemy = enemyData->enemy;
	D3DXVECTOR2 dis = enemy->GetDisToPlayer();
	D3DXVECTOR2 accelerate = D3DXVECTOR2(0, 0);
	//SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
	
	//AddVelocity(accelerate);

	//Enemy::Update(dt);
}

void Bat::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
	Enemy::OnCollision(impactor, side, collisionTime, dt);
}

void Bat::SetState(EnemyState::eState state)
{
	if ((state == EnemyState::Follow)) {
		enemyData->enemyState = batFollowPlayerState;
		currentStateName = EnemyState::Follow;
	}
	else if ((state == EnemyState::Idle)) {
		enemyData->enemyState = batIdleState;
		currentStateName = EnemyState::Idle;
	}
	enemyData->enemyState->ResetState();
}

void Bat::Spawn()
{
	SetState(EnemyState::Idle);
	Enemy::Spawn();
}
