#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class BlueVase : public Item {
	Sprites* sprite;
public:
	BlueVase();
	~BlueVase();
	void Update(float dt) override;
	void Render() override;

};