#pragma once
#include "Entity.h"

class Enemy : public Entity {
protected:
	bool isDisappeared;
	BoxCollider collider;
	BoxCollider spawnBox;
	D3DXVECTOR3 spawnPosition;
	int spawnDirector;

public:
	Enemy();
	~Enemy();

	virtual void Update(float dt);
	virtual void Render();

	void SetSpawnBox(BoxCollider box, int direction);

	BoxCollider GetRect() override;

	float GetWidth() override;
	float GetHeight() override;

	void SetActive(bool active) override;

	//void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;

	void Spawn();
};