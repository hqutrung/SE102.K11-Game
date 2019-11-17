#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class ChainedPillar : public Item {
	Sprites* sprite;
public:
	ChainedPillar();
	~ChainedPillar();
	void Update(float dt) override;
	void Render() override;

};