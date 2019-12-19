#pragma once
#include "Item.h"
#include "Textures.h"

class Gem : public Item {
public:
	Gem();
	void OnDestroy() override;
};