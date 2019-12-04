#include "EnemyState.h"
#include"Enemy.h"

EnemyState::EnemyState(EnemyData* data)
{
	this->enemyData = data;
}

EnemyState::~EnemyState()
{
}
void EnemyState::Update(float dt)
{
	e_Animation->Update(dt);
}

void EnemyState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::LeftToRight);
}


void EnemyState::ResetState(int dummy)
{
	e_Animation->ResetAnimation();
}

