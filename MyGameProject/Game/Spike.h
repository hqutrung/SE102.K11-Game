#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class Spike : public Obstacles {
public:
	Spike();
	~Spike();
	void SetSpawnBox(BoxCollider box, int id) override;
	void Update(float dt) override;
};