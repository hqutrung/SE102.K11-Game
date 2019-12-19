#include "EnemyState.h"
#include "Enemy.h"

EnemyState::EnemyState(EnemyData* data){
	this->enemyData = data;
	//enemyData->enemy->currentStateName = Follow;
}

EnemyState::~EnemyState()
{
	delete e_Animation;
	e_Animation = NULL;
}
void EnemyState::Update(float dt)
{
	e_Animation->Update(dt);
}

void EnemyState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::LeftToRight);
}


void EnemyState::ResetState()
{
	e_Animation->countLoopFrame = 1;
	e_Animation->ResetAnimation();
}

