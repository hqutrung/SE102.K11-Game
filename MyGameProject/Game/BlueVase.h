#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class BlueVase : public Obstacles {

public:
	BlueVase();
	void Update(float dt) override;
	void Render()override;
};