#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Pillar : public Item {
	Sprites* sprite;
public:
	Pillar();
	~Pillar();
	void Update(float dt) override;
	void Render() override;

};