#pragma once
#include "Entity.h"
#include "Animation.h"

class Item : public Entity {
protected:
	bool isDisappeared;
	BoxCollider spawnBox;
	Animation* animation;

public:
	Item();
	~Item();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetSpawnBox(BoxCollider box);
	virtual BoxCollider GetSpawnBox();
	BoxCollider GetRect() override;

	void SetActive(bool active) override;
	void MakeInactive();
	void Spawn();

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60);

};