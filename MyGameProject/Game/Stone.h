#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class Stone : public Obstacles {
public:
	Stone();
	~Stone();
	void SetSpawnBox(BoxCollider box, int id) override;
	void Update(float dt) override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
};
