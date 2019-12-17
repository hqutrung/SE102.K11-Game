#pragma once
#include "Item.h"
#include "Textures.h"

class Apple : public Item {
public:
	Apple();
	~Apple();
	void Update(float dt) override;
	void OnDestroy() override;
};