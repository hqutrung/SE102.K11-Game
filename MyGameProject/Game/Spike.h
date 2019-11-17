#pragma once
#include "Item.h"
#include "Textures.h"
#include "Animation.h"

class Spike : public Item {
	Animation* animation;
public:
	Spike();
	~Spike();
	void Update(float dt) override;
	void Render() override;

};