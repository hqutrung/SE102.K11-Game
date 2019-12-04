#pragma once
#include "Entity.h"
#include "Animation.h"

class Enemy : public Entity {
protected:
	BoxCollider collider;
	BoxCollider spawnBox;
	D3DXVECTOR3 spawnPosition;
	Entity::MoveDirection spawnDirection;
	virtual void Spawn();
	virtual void MakeInactive();
	Animation* animation;
	D3DXVECTOR3 disToPlayer, firstPos;


public:
	Enemy();
	~Enemy();

	virtual void Update(float dt);
	virtual void Render();

	virtual BoxCollider GetRect();
	virtual BoxCollider GetSpawnBox();
	virtual Entity::MoveDirection GetSpawnDirection();

	virtual void SetRect(BoxCollider box);
	void SetSpawnBox(BoxCollider box, int direction);
	void SetActive(bool active) override;

	float GetWidth() override;
	float GetBigWidth() override;
	float GetHeight() override;
	float GetBigHeight() override;


	virtual void SetColliderTop(float top);
	virtual void SetColliderLeft(float left);
	virtual void SetColliderBottom(float bottom);
	virtual void SetColliderRight(float right);

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60);

	virtual bool followPlayer(D3DXVECTOR3 dispos);
};