#pragma once
#include "Entity.h"

class Item : public Entity {
protected:
	bool isDisappeared;
	BoxCollider collider;
	D3DXVECTOR3 spawnPosition;
	
public:
	Item();
	~Item();

	virtual void Update(float dt);
	virtual void Render();

	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);

	virtual void ResetState();

	void SetSpawnBox(BoxCollider box);

	BoxCollider GetRect() override;

	float GetWidth() override;
	float GetHeight() override;

	void SetActive(bool active) override;

	//void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;

	void Spawn();
};