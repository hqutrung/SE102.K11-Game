#include "JafarAttackState.h"

JafarAttackState::JafarAttackState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_JAFAR), 1, 2, 1, 8, 8, 2, 10, 0.11f, D3DCOLOR_XRGB(255, 0, 255));
	isReloading = false;
	attackTime = 0.3f;
	delaytime = 0.12f;
}

void JafarAttackState::Update(float dt)
{
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0);

	if (e_Animation->GetCurrentFrameID() == 4 || isReloading) {
		if (attackTime <= 0) {
			e_Animation->Update(dt);
			if (e_Animation->GetCurrentFrameID() == 3) {
				attackTime = 0.3f;
				isReloading = false;
			}
			return;
		}
		else {
			if (delaytime <= 0) {
				if (!ObjectPooling::GetInstance()->CheckQuantity(JAFAR_WEAPON_INDEX))
					return;
				UseWeapon();
				attackTime -= dt;
				delaytime = 0.12f;
				if (attackTime < 0)
					isReloading = true;
			}
			delaytime -= dt;
			return;
		}
	}
	e_Animation->Update(dt);
}

void JafarAttackState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void JafarAttackState::ResetState()
{
}

void JafarAttackState::UseWeapon()
{
	auto pos = enemyData->enemy->GetPosition();
	//pos.y -= 15;
	ObjectPooling* pool = ObjectPooling::GetInstance();
	if (ObjectPooling::GetInstance()->SingleInstantiate(JAFAR_WEAPON_INDEX, pos)) {
		Sound::GetInstance()->PlayFX(JAFAR_TRACTOR);
	}
}
