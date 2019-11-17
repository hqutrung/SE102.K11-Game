#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Spike : public Item {
	Sprites* sprite;
public:
	Spike();
	~Spike();
	void Update(float dt) override;
	void Render() override;

};