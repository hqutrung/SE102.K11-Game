#pragma once
#include "Entity.h"
#include "Player.h"
#include "EnemyData.h"
#include"EnemyState.h"

class Enemy : public Entity {
protected:
	BoxCollider spawnBox;
	D3DXVECTOR3 spawnPosition;
	Entity::MoveDirection spawnDirection;
	int point;
	D3DXVECTOR2 disToPlayer;

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
	virtual void SetSpawnBox(BoxCollider box, int direction);

	void SetActive(bool active) override;
	virtual void SetState(EnemyState::eState state);

	virtual BoxCollider GetRect();
	virtual BoxCollider GetSpawnBox();
	virtual D3DXVECTOR3 GetSpawnPosition() { return spawnPosition; }
	virtual Entity::MoveDirection GetSpawnDirection();
	D3DXVECTOR2 GetDisToPlayer() { return disToPlayer; }

	float GetWidth() override;
	float GetBigWidth() override;
	float GetHeight() override;
	float GetBigHeight() override;
	bool isInjured = false;
	bool isAttack = false;
	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = 1.0f / 60);
};