#include "Bat.h"

Bat::Bat() : Enemy()
{
	SetTag(BAT);
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BAT, "Resources/Enemys/bat.png", D3DCOLOR_XRGB(255, 0, 255));
	batFollowPlayerState = new BatFollowPlayerState(enemyData);
	batIdleState = new BatIdleState(enemyData);
	batRotateState = new BatRotateState(enemyData);
	isCollidable = true;
	isAttack = true;
	point = 200;
	Hp = 1;
}

Bat::~Bat()
{
	delete batFollowPlayerState;
	batFollowPlayerState = NULL;
	delete batIdleState;
	batIdleState = NULL;
	delete batRotateState;
	batRotateState = NULL;
	Enemy::~Enemy();
}

void Bat::Update(float dt)
{
	auto enemy = enemyData->enemy;
	D3DXVECTOR2 dis = enemy->GetDisToPlayer();
	D3DXVECTOR2 accelerate = D3DXVECTOR2(0, 0);
	Enemy::Update(dt);
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
	else if ((state == EnemyState::Rotate)) {
		enemyData->enemyState = batRotateState;
		currentStateName = EnemyState::Rotate;
	}
	enemyData->enemyState->ResetState();
}

void Bat::Spawn()
{
	SetState(EnemyState::Idle);
	Enemy::Spawn();

	enemyData->enemy->SetBodyBox(13, -13, 13, -13);
	collider = bodyBox;
}

