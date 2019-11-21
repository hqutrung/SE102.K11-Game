#pragma once
#include "Item.h"
#include "Textures.h"
#include "Animation.h"

class BlueVase : public Item {
	Animation* animation;
public:
	BlueVase();
	~BlueVase();
	void Update(float dt) override;
	void Render() override;

};