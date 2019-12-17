#include "JafarAttackState.h"

JafarAttackState::JafarAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_JAFAR), 1, 2, 1, 8, 8, 2, 10, 0.04f, D3DCOLOR_XRGB(255, 0, 255));
	delayTime = 0.15f;
}

void JafarAttackState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);
	e_Animation->Update(dt);
	delayTime -= dt;
	if (delayTime <= 0) {
		if (!ObjectPooling::GetInstance()->CheckQuantity(SNAKE_WEAPON_INDEX))
			return;
		UseWeapon();
		delayTime = 0.15f;
	}
}

void JafarAttackState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void JafarAttackState::ResetState()
{
	auto e = enemyData->enemy;
	e->SetColliderLeft(-15);
	e->SetColliderRight(24);
	e->SetColliderTop(33);
	e->SetColliderBottom(-26);
	e->SetBodyBox(32, -15, 26, -26);
}

void JafarAttackState::UseWeapon()
{
	auto pos = enemyData->enemy->GetPosition();
	//pos.y -= 15;
	ObjectPooling* pool = ObjectPooling::GetInstance();
	if (ObjectPooling::GetInstance()->SingleInstantiate(JAFAR_WEAPON_INDEX, pos)) {
		// Play Sound
	}
}
