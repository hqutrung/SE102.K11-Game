#pragma once
#include "Entity.h"
#include "Animation.h"

class Obstacles : public Entity {
protected:
	BoxCollider spawnBox;
	Animation* animation;
	int id;	// Xu ly trat tu Obstacles
	float delayTime;
public:
	Obstacles();
	~Obstacles();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetSpawnBox(BoxCollider box, int id);
	virtual BoxCollider GetSpawnBox();
	BoxCollider GetRect() override;

	void SetActive(bool active) override;
	void MakeInactive();
	void Spawn();

	Animation* GetAnimation();
};