#include "SnakeAttackState.h"

SnakeAttackState::SnakeAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_JAFAR), 1, 9, 2, 9, 10, 2, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));

}

void SnakeAttackState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	e_Animation->Update(dt);
	
	if (e_Animation->IsLastFrame(dt)) {
		if (!ObjectPooling::GetInstance()->CheckQuantity(SNAKE_WEAPON_INDEX))
			return;
		PuffFire();
	}
}

void SnakeAttackState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::RightToLeft);

}

void SnakeAttackState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-15);
	e->SetColliderRight(24);
	e->SetColliderTop(33);
	e->SetColliderBottom(-26);
	e->SetBodyBox(32, -15, 26, -26);
}

void SnakeAttackState::PuffFire()
{
	auto pos = enemyData->enemy->GetPosition();
	pos.y -= 15;
	ObjectPooling* pool = ObjectPooling::GetInstance();
	if (ObjectPooling::GetInstance()->SingleInstantiate(SNAKE_WEAPON_INDEX, pos)){
		// Play Sound
	}
}
