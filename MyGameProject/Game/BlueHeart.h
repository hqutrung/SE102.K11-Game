#pragma once
#include "Item.h"
#include "Textures.h"

class BlueHeart : public Item {
public:
	BlueHeart();
	void OnDestroy() override;
};