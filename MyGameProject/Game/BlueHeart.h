#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class BlueHeart : public Item {
	Sprites* sprite;
public:
	BlueHeart();
	~BlueHeart();
	void Update(float dt) override;
	void Render() override;

};