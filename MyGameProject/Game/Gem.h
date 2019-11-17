#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Gem : public Item {
	Sprites* sprite;
public:
	Gem();
	~Gem();
	void Update(float dt) override;
	void Render() override;
};