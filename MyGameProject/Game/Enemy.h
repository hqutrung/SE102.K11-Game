#pragma once
#include "Entity.h"
#include "EnemyData.h"
#include"EnemyState.h"

class Enemy : public Entity {
protected:
	BoxCollider spawnBox;
	D3DXVECTOR3 spawnPosition;
	Entity::MoveDirection spawnDirection;
	int point;

	// Colission
	float collisionTime;
	SideCollision side;

	EnemyData* enemyData;

	virtual void Spawn();
	virtual void MakeInactive();

public:
	Enemy();
	virtual ~Enemy();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetRect(BoxCollider box);
	void SetSpawnBox(BoxCollider box, int direction);

	void SetActive(bool active) override;
	virtual void SetState(EnemyState::eState state);

	virtual BoxCollider GetRect();
	virtual BoxCollider GetSpawnBox();
	virtual Entity::MoveDirection GetSpawnDirection();

	float GetWidth() override;
	float GetBigWidth() override;
	float GetHeight() override;
	float GetBigHeight() override;

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60);
};