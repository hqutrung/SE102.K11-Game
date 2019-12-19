#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class Ball : public Obstacles {
public:
	Ball();
	void SetSpawnBox(BoxCollider box, int id) override;
	void Update(float dt) override;
};