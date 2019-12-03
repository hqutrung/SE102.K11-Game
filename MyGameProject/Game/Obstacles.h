#pragma once
#include "Entity.h"
#include "Animation.h"

class Obstacles : public Entity {
protected:
	bool isDisappeared;
	BoxCollider collider;
	D3DXVECTOR3 spawnPosition;
	BoxCollider spawnBox;
	Animation* animation;

public:
	Obstacles();
	~Obstacles();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);

	void SetSpawnBox(BoxCollider box);
	void SetActive(bool active) override;

	BoxCollider GetRect() override;
	void MakeInactive();

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60);

	void Spawn();

	Animation* GetAnimation() { return animation; };
};