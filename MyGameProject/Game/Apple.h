#pragma once
#include "Item.h"
#include "Textures.h"

class Apple : public Item {
public:
	Apple();
	void Update(float dt) override;
	void OnDestroy() override;
	void SetSpawnBox1(int top, int left, int bot, int right);
};