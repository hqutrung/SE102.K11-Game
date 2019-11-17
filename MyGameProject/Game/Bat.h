#pragma once
#include "Enemy.h"
#include "Sprites.h"
#include "Textures.h"

class Bat : public Enemy {
	Sprites* sprite;
public:
	Bat();
	~Bat();
	void Update(float dt) override;
	void Render() override;
};
