#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Apple : public Item {
	Sprites* sprite;
public:
	Apple();
	~Apple();
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
};