#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class BlueVase : public Obstacles {

public:
	BlueVase();
	~BlueVase();
	void Update(float dt) override;
};