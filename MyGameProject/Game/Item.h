#pragma once
#include "Entity.h"

class Item : public Entity {
protected:
	bool isDisappeared;
	BoxCollider collider;
	D3DXVECTOR3 spawnPosition;
	BoxCollider spawnBox;
	float collisionTime;
	SideCollision side;

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

	virtual void SetColliderTop(float top);
	virtual void SetColliderLeft(float left);
	virtual void SetColliderBottom(float bottom);
	virtual void SetColliderRight(float right);

	BoxCollider GetRect() override;
	float GetWidth() override;
	float GetHeight() override;
	void SetActive(bool active) override;
	void MakeInactive();

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60);

	void Spawn();
};