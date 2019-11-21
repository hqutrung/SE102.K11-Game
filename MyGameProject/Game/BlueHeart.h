#pragma once
#include "Item.h"
#include "Textures.h"
#include "Animation.h"

class BlueHeart : public Item {
	Animation* animation;
public:
	BlueHeart();
	~BlueHeart();
	void Update(float dt) override;
	void Render() override;

};