#pragma once
#include "GameConfig.h"
#include "Textures.h"
#include "Animation.h"
#include "Entity.h"
#include "Camera.h"


class DemoEnemy : public Entity {
public:
	DemoEnemy();
	~DemoEnemy();

	void Update(float dt);
	void Render();
	//void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60);

protected:
	Animation* m_Animation;
};