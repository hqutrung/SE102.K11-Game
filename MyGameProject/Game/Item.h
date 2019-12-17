#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Effect.h"
#include "SmallItemExplosion.h"
#include "Grid.h"
#include "Player.h"

class Item : public Entity {
protected:
	bool isDisappeared;
	BoxCollider spawnBox;
	Animation* animation;
	EffectChain* effect;

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
	void OnDestroy() override;
};