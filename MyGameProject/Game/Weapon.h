#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Effect.h"

class Weapon : public Entity {
public:
	Weapon();
	virtual ~Weapon();

	virtual void Update(float dt);
	virtual void Render();

	virtual BoxCollider GetRect();
	virtual void SetActive(bool active);

	virtual float GetWidth();
	virtual float GetBigWidth();
	virtual float GetHeight();
	virtual float GetBigHeight();

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = 1.0 / 60);
	virtual void Instantiate(D3DXVECTOR3 position);
	virtual void OnDestroy();
protected:
	virtual void MakeInactive();
	virtual void Spawn();
	bool isDissapeared;
	Animation* animation;
};
