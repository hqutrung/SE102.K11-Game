#include "JafarIdleState.h"

JafarIdleState::JafarIdleState(EnemyData* data) : EnemyState(data)
{
	e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_JAFAR), 1, 1, 1, 1, 10, 2, 10, 0.04f, D3DCOLOR_XRGB(255, 0, 255));
	delaytime = 0.1f;
}

void JafarIdleState::Update(float dt)
{
	/*auto player = Player::GetInstance();
	auto enemy = enemyData->enemy;
	bool isCol = CollisionDetector::IsCollide(player->GetRect(), enemy->GetBody());
	if (isCol & !Jafar::GetInstance()->IsSnake()) {
		if(delaytime <=0)
			enemy->SetState(EnemyState::Attack);
		delaytime -= dt;
	}
	else
		delaytime = 0.1f;*/
	auto enemy = enemyData->enemy;
	enemy->SetVx(0);
	enemy->SetVy(0); 
	
	e_Animation->Update(dt);
}

void JafarIdleState::Render()
{
	e_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}

void JafarIdleState::ResetState()
{
	auto e = enemyData->enemy;/*
	e->SetColliderLeft(-15);
	e->SetColliderRight(24);
	e->SetColliderTop(33);
	e->SetColliderBottom(-26);
	e->SetBodyBox(32, -15, 26, -26);*/
}
